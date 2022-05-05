mod meta;
mod error;

use std::collections::HashMap;
use std::path::{Path, PathBuf};
use std::fs;
use std::fs::File;

#[macro_use]
extern crate slog;

pub use crate::error::Result;
use crate::meta::{FileIndex, LogFile, Meta};

type MemIndex = HashMap<String, String>;

/// KvStore is a key-value storage.
pub struct KvStore {
    meta: Meta,
    mem_index: MemIndex,
}

impl KvStore {
    /// Create a new `KvStore` object.
    // pub fn new() -> Self {
    //     Self {
    //         data: HashMap::default(),
    //     }
    // }

    /// Open a path and create the `KvStore` object.
    pub fn open(path: impl Into<PathBuf>) -> Result<KvStore> {
        let mut max_file_id = 0;
        let mut file_index = FileIndex::default();

        let new_log_file = |file_id, path: &Path, file_index: &mut FileIndex| -> Result<()> {
            let log_file = LogFile {
                id: file_id,
                file: File::options().read(true).open(path)?,
            };
            file_index.insert(file_id, log_file);
            info!("Found log file: {}", path);
            Ok(())
        };

        for entry in fs::read_dir(path.into())? {
            let entry = entry?;
            let path = entry.path();
            if let (Some(stem), Some(Some("dat"))) = (path.file_stem(), path.extension().map(|s| s.to_str())) {
                if let Ok(file_id) = stem.to_string_lossy().parse::<u64>() {
                    new_log_file(file_id, path.as_path(), &mut file_index)?;
                    if max_file_id < file_id {
                        max_file_id = file_id;
                    }
                }
            }
        }

        let is_create = file_index.is_empty();

        let mut_file_name = format!("{}.dat", max_file_id);
        let mut_file_path = Path::new(&mut_file_name);
        let mut_log_file = File::options().create_new(is_create).append(true).open(mut_file_path)?;

        if is_create {
            new_log_file(max_file_id, &mut_file_path, &mut file_index)?;
        }

        let meta = Meta {
            max_file_id,
            file_index,
            mut_log_file: LogFile {
                id: max_file_id,
                file: mut_log_file,
            },
        };

        Ok(Self {
            meta,
            mem_index: MemIndex::default(),
        })
    }

    /// Set entry of `key` with `value`.
    pub fn set(&mut self, key: String, value: String) -> Result<()> {
        self.mem_index.insert(key, value);
        Ok(())
    }

    /// Get value of `key`. None if entry not exist.
    pub fn get(&self, key: String) -> Result<Option<String>> {
        Ok(self.mem_index.get(&key).cloned())
    }

    /// Remove entry of `key`. Will do nothing if entry not exist.
    pub fn remove(&mut self, key: String) -> Result<()> {
        self.mem_index.remove(&key);
        Ok(())
    }
}
