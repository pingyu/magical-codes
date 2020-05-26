use crate::error::KvError;
use byteorder::{LittleEndian, ReadBytesExt, WriteBytesExt};
use chrono::Local;
use serde::{Deserialize, Serialize};
use std::collections::HashMap;
use std::fs::{File, OpenOptions};
use std::io::{BufReader, ErrorKind, Read, Seek, SeekFrom, Write};
use std::path::Path;

pub type Result<T> = std::result::Result<T, KvError>;

/**************** Command ****************/
#[derive(Serialize, Deserialize, Debug)]
#[serde(tag = "type")]
enum Command {
    S { k: String, v: String }, // Set
    R { k: String },            // Remove
}

/**************** KvStore *****************/
pub struct KvStore {
    map: HashMap<String, u64>,
    rdr: BufReader<File>,
    wal: File,
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
        let mut m = HashMap::new();
        let f = OpenOptions::new()
            .read(true)
            .write(true)
            .create(true)
            .open(&path)?;
        let mut rdr = BufReader::new(f);
        while let Some((cmd, pos)) = Self::read_record(&mut rdr)? {
            match cmd {
                Command::S { k, v: _ } => {
                    m.insert(k, pos);
                }
                Command::R { k } => {
                    m.remove(&k);
                }
            }
        }

        let kvs = KvStore {
            map: m,
            rdr,
            wal: OpenOptions::new().append(true).create(true).open(&path)?,
        };
        Ok(kvs)
    }

    fn write_record(f: &mut File, cmd: &Command) -> Result<()> {
        let ts = Local::now().timestamp();
        let js = serde_json::to_vec(&cmd)?;
        let length = js.len();

        // let mut w = BufWriter::new(f);
        let mut wtr = vec![];
        wtr.write_u8(PROTO_ST)?;
        wtr.write_i64::<LittleEndian>(ts)?;
        wtr.write_u64::<LittleEndian>(length as u64)?;
        wtr.write_all(&js)?;
        wtr.write_u8(PROTO_ET)?;

        // let pos = self.f.seek(SeekFrom::End(0))?;
        f.write_all(&wtr)?;
        f.flush()?;
        Ok(())
    }

    fn read_record(rdr: &mut BufReader<File>) -> Result<Option<(Command, u64)>> {
        let pos = rdr.seek(SeekFrom::Current(0))?;
        match rdr.read_u8() {
            Err(ref err) if err.kind() == ErrorKind::UnexpectedEof => {
                return Ok(None);
            }
            Err(err) => {
                return Err(KvError::Io(err));
            }
            Ok(n) if n != PROTO_ST => {
                return Err(KvError::FormatNoStartMark(rdr.seek(SeekFrom::Current(0))?));
            }
            _ => {}
        }
        let _ts = rdr.read_i64::<LittleEndian>()?;
        let length = rdr.read_u64::<LittleEndian>()?;

        let mut buf = Vec::with_capacity(length as usize);
        buf.resize(length as usize, 0);
        rdr.read_exact(&mut buf[..])?;

        if rdr.read_u8()? != PROTO_ET {
            return Err(KvError::FormatNoEndMark(rdr.seek(SeekFrom::Current(0))?));
        }

        let cmd = serde_json::from_slice::<Command>(&buf[..])?;
        Ok(Some((cmd, pos)))
    }

    fn read_record_at(rdr: &mut BufReader<File>, pos: u64) -> Result<Command> {
        rdr.seek(SeekFrom::Start(pos))?;
        let _st = rdr.read_u8()?;
        let _ts = rdr.read_i64::<LittleEndian>()?;
        let length = rdr.read_u64::<LittleEndian>()?;
        let mut buf = Vec::with_capacity(length as usize);
        buf.resize(length as usize, 0);
        rdr.read_exact(&mut buf[..])?;
        let _et = rdr.read_u8()?;

        let cmd = serde_json::from_slice::<Command>(&buf)?;
        Ok(cmd)
    }

    pub fn set(&mut self, key: String, val: String) -> Result<()> {
        let cmd = Command::S { k: key, v: val };
        Self::write_record(&mut self.wal, &cmd)?;

        // self.map.insert(key, val);
        Ok(())
    }

    pub fn get(&mut self, key: String) -> Result<Option<String>> {
        if let Some(pos) = self.map.get(&key) {
            let cmd = Self::read_record_at(&mut self.rdr, *pos)?;
            match cmd {
                Command::S { k: _, v } => Ok(Some(v.to_owned())),
                _ => Err(KvError::FormatNotSetCommandInMap(key.to_owned(), *pos)),
            }
        } else {
            Ok(None)
        }
    }

    pub fn remove(&mut self, key: String) -> Result<()> {
        let cmd = Command::R { k: key };
        Self::write_record(&mut self.wal, &cmd)?;
        // self.map.remove(&key);
        Ok(())
    }
}
