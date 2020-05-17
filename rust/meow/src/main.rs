#[macro_use]
extern crate clap;
use clap::App;
#[macro_use]
extern crate dotenv_codegen;

fn main() {
    let yaml = load_yaml!("cli.yml");
    let m = App::from_yaml(yaml).get_matches();

    match m.value_of("argument1") {
        _ => println!("others"),
    }
    // let args: Vec<String> = env::args().collect();
    // println!("{:?}", args);

    println!("{}", dotenv!("PORT"));
}
