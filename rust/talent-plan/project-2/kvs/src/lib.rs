// #[macro_use] extern crate failure_derive;

pub use error::KvError;
pub use kv::{KvStore, Result};

mod error;
mod kv;
