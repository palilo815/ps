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
        for c in s.chars() {
            let c = match c {
                ' ' => "%20",
                '!' => "%21",
                '$' => "%24",
                '%' => "%25",
                '(' => "%28",
                ')' => "%29",
                '*' => "%2a",
                _ => &c.to_string(),
            };
            write!(bw, "{c}").ok();
        }
        writeln!(bw).ok();
    }
}
