use clap::{crate_version, load_yaml, App};
use kvs::KvStore;
use std::process;

fn main() {
    let yaml = load_yaml!("cli.yml");
    let app = App::from(yaml).version(crate_version!());
    let m = app.get_matches();

    let mut _kvs = KvStore::new();

    match m.subcommand() {
        ("get", Some(_sub_m)) => {
            // let key = sub_m.index_of("KEY").unwrap();
            // kvs.get(key.to_string());
            // process::exit(0);
            panic!("unimplemented");
        }
        ("set", Some(_sub_m)) => {
            // let key = sub_m.index_of("KEY").unwrap();
            // let val = sub_m.index_of("VALUE").unwrap();
            // kvs.set(key.to_string(), val.to_string());
            // process::exit(0);
            panic!("unimplemented");
        }
        ("rm", Some(_sub_m)) => {
            // let key = sub_m.index_of("KEY").unwrap();
            // kvs.remove(key.to_string());
            // process::exit(0);
            panic!("unimplemented");
        }
        _ => {}
    }

    process::exit(1);
}
