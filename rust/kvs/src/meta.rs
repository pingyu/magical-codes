use std::collections::HashMap;
use std::fs::File;

#[derive(Debug)]
pub(crate) struct LogFile {
    pub id: u64,
    pub file: File,
}

pub(crate) type FileIndex = HashMap<u64, LogFile>;

#[derive(Debug)]
pub(crate) struct Meta {
    pub max_file_id: u64,
    pub file_index: FileIndex,
    pub mut_log_file: LogFile,
}

// pub struct MetaFile {
//     max_file_id: u64,
// }
