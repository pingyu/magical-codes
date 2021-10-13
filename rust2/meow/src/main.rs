#[macro_use]
extern crate clap;
extern crate dotenv_codegen;

use clap::App;
use dotenv_codegen::dotenv;
// use std::env;

fn main() {
    println!("Hello, world!");
    println!("{}", dotenv!("PORT"));

    // let args: Vec<String> = env::args().collect();
    // println!("{:?}", args);

    let yaml = load_yaml!("cli.yml");
    let _m = App::from_yaml(yaml).get_matches();

    // match m.value_of("argument1") {}
}
