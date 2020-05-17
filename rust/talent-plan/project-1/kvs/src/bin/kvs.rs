#[macro_use]
extern crate clap;
use clap::App;
use kvs::KvStore;
use std::process::exit;

fn main() {
    let yaml = load_yaml!("cli.yml");
    let matches = App::from_yaml(yaml)
        .author(crate_authors!())
        .version(crate_version!())
        .get_matches();

    let mut kvs = KvStore::new();

    match matches.subcommand() {
        ("get", Some(sub_m)) => {
            let key = sub_m.value_of("KEY").unwrap();
            // println!("get {}", key);
            // kvs.get(key.to_owned());
            eprintln!("unimplemented");
            exit(1);
        }
        ("set", Some(sub_m)) => {
            let key = sub_m.value_of("KEY").unwrap();
            let val = sub_m.value_of("VALUE").unwrap();
            // println!("set {} {}", key, val);
            // kvs.set(key.to_owned(), val.to_owned());
            eprintln!("unimplemented");
            exit(1);
        }
        ("rm", Some(sub_m)) => {
            let key = sub_m.value_of("KEY").unwrap();
            // kvs.remove(key.to_owned());
            eprintln!("unimplemented");
            exit(1);
        }
        _ => {
            // eprint!("{}", matches.usage());
            exit(1);
        }
    }
}
