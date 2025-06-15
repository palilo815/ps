use std::io::*;

fn main() {
    let mut bw = BufWriter::new(stdout().lock());
    let mut s = String::new();
    stdin().read_to_string(&mut s).ok();
    let mut it = s.split('\n');
    loop {
        let s = it.next().unwrap();
        if s == "#" {
            break;
        }
        for word in s.split_ascii_whitespace() {
            let mut word = word.bytes().collect::<Vec<_>>();
            let len = word.len();
            if len > 2 {
                word[1..len - 1].reverse();
            }
            write!(bw, "{} ", String::from_utf8(word).unwrap()).ok();
        }
        writeln!(bw).ok();
    }
}
