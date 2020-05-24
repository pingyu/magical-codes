use bson;
use byteorder::{LittleEndian, WriteBytesExt};
use chrono::Local;
use serde::{Deserialize, Serialize};
use std::collections::HashMap;
use std::fs::{File, OpenOptions};
use std::io::Write;
use std::path::Path;

use crate::error::KvError;
pub type Result<T> = std::result::Result<T, KvError>;

/**************** Command ****************/
#[derive(Serialize, Deserialize, Debug)]
#[serde(tag = "type")]
enum Command<'a> {
    S { k: &'a str, v: &'a str }, // Set
    R { k: &'a str },             // Remove
}

/**************** KvStore *****************/
pub struct KvStore {
    map: HashMap<String, String>,
    f: File,
}

const PROTO_ST: u8 = 0x12;
const PROTO_ET: u8 = 0x34;

impl KvStore {
    // pub fn new() -> KvStore {
    //     KvStore {
    //         map: HashMap::new(),
    //         f: None,
    //     }
    // }

    pub fn open<P: AsRef<Path>>(path: P) -> Result<KvStore> {
        let kvs = KvStore {
            map: HashMap::new(),
            f: OpenOptions::new()
                .read(true)
                .append(true)
                .create(true)
                .open(path)?,
        };
        Ok(kvs)
    }

    fn write_record(f: &mut File, cmd: &Command) -> Result<()> {
        let ts = Local::now().timestamp();
        let bs = bson::to_bson(&cmd)?;
        let bss = bs.to_string();
        let buf = bss.as_bytes();
        let length = buf.len();

        // let mut w = BufWriter::new(f);
        let mut wtr = vec![];
        wtr.write_u8(PROTO_ST)?;
        wtr.write_i64::<LittleEndian>(ts)?;
        wtr.write_u64::<LittleEndian>(length as u64)?;
        wtr.write_all(buf)?;
        wtr.write_u8(PROTO_ET)?;

        f.write_all(&wtr)?;
        f.flush()?;
        Ok(())
    }

    pub fn set(&mut self, key: String, val: String) -> Result<()> {
        let cmd = Command::S { k: &key, v: &val };
        Self::write_record(&mut self.f, &cmd)?;

        self.map.insert(key, val);
        Ok(())
    }

    pub fn get(&mut self, key: String) -> Result<Option<String>> {
        Ok(self.map.get(&key).map(|x| x.to_owned()))
    }

    pub fn remove(&mut self, key: String) -> Result<()> {
        self.map.remove(&key);
        Ok(())
    }
}
