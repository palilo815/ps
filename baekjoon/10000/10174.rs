use std::io::*;

fn main() {
    let mut s = String::new();
    stdin().read_to_string(&mut s).ok();
    let mut it = s.leak().split('\n');
    let n = it.next().unwrap().parse::<usize>().unwrap();
    for _ in 0..n {
        let t = it.next().unwrap().to_ascii_lowercase();
        let f = t.bytes().eq(t.bytes().rev());
        println!("{}", if f { "Yes" } else { "No" });
    }
}
