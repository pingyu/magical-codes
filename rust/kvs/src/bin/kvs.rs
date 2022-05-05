use clap::{Parser, Subcommand};
use kvs::{Result, KvStore};
use slog::Drain;

#[macro_use]
extern crate slog;

#[derive(Parser, Debug)]
#[clap(author, version, about, long_about = "kvs is a key-value store")]
struct Args {
    #[clap(subcommand)]
    command: Commands,
}

#[derive(Subcommand, Debug)]
enum Commands {
    Set { key: String, value: String },
    Get { key: String },
    Rm { key: String },
}

fn init_log() -> slog::Logger {
    let decorator = slog_term::TermDecorator::new().build();
    let drain = slog_term::FullFormat::new(decorator).build().fuse();
    let drain = slog_async::Async::new(drain).build().fuse();
    slog::Logger::root(drain, o!())
}

fn main() -> Result<()> {
    let _log = init_log();

    let args = Args::parse();
    // println!("Hello, world: {:?}", args);

    let mut store = KvStore::open("data")?;
    match args.command {
        Commands::Set { key, value } => store.set(key, value)?,
        Commands::Get { key } => {
            let _ = store.get(key)?;
        }
        Commands::Rm { key } => store.remove(key)?,
    }

    Ok(())
}
