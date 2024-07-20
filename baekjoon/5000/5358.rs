use std::io::*;

fn main() {
    let mut bw = BufWriter::new(stdout().lock());
    let mut s = String::new();
    stdin().read_to_string(&mut s).ok();
    let mut it = s.split_ascii_whitespace();
    while let (Some(x), Some(y)) = (it.next(), it.next()) {
        let is_ei = |c: u8| c == b'e' || c == b'E' || c == b'i' || c == b'I';
        let x = x.bytes().map(|c| if is_ei(c) { c ^ 12 } else { c });
        let y = y.bytes().map(|c| if is_ei(c) { c ^ 12 } else { c });
        let x = String::from_utf8(x.collect()).unwrap();
        let y = String::from_utf8(y.collect()).unwrap();
        writeln!(bw, "{x} {y}").ok();
    }
}
