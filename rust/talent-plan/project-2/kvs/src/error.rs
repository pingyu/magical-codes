use failure::Fail;
use std::io;

#[derive(Fail, Debug)]
pub enum KvError {
    #[fail(display = "unknown error")]
    Unknown,
    #[fail(display = "{}", _0)]
    Io(#[cause] io::Error),
    #[fail(display = "{}", _0)]
    Encode(#[cause] bson::EncoderError),
}

impl From<io::Error> for KvError {
    fn from(err: io::Error) -> KvError {
        KvError::Io(err)
    }
}

impl From<bson::EncoderError> for KvError {
    fn from(err: bson::EncoderError) -> KvError {
        KvError::Encode(err)
    }
}
