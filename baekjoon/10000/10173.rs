use std::io::*;

fn main() {
    let mut s = String::new();
    stdin().read_to_string(&mut s).ok();
    let mut it = s.leak().split('\n');
    loop {
        let s = it.next().unwrap();
        if s == "EOI" {
            break;
        }
        let found = s.to_ascii_lowercase().contains("nemo");
        println!("{}", if found { "Found" } else { "Missing" });
    }
}
