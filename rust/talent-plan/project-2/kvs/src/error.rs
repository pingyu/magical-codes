use failure::Fail;
use std::io;

#[derive(Fail, Debug)]
pub enum KvError {
    #[fail(display = "unknown error")]
    Unknown,
    #[fail(display = "{}", _0)]
    Io(#[cause] io::Error),
    #[fail(display = "{}", _0)]
    Encode(#[cause] serde_json::Error),
    #[fail(display = "format error: no start mark, pos: {}", _0)]
    FormatNoStartMark(u64),
    #[fail(display = "format error: no end mark, pos: {}", _0)]
    FormatNoEndMark(u64),
    #[fail(
        display = "format error: not set command in map, key:{}, pos:{}",
        _0, _1
    )]
    FormatNotSetCommandInMap(String, u64),
}

impl From<io::Error> for KvError {
    fn from(err: io::Error) -> KvError {
        KvError::Io(err)
    }
}

impl From<serde_json::Error> for KvError {
    fn from(err: serde_json::Error) -> KvError {
        KvError::Encode(err)
    }
}
