use std::{io, result};
use thiserror::Error;

#[derive(Error, Debug)]
pub enum KvError {
    #[error("Io error: {0:?}")]
    Io(#[from] io::Error),
}

pub type Result<T> = result::Result<T, KvError>;
