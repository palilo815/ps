use std::io::*;

fn main() {
    let mut s = String::new();
    stdin().read_to_string(&mut s).ok();
    let mut it = s.split('\n');
    let mut bw = BufWriter::new(stdout().lock());
    for t in 1.. {
        let s = it.next().unwrap();
        if s == "# #" {
            break;
        }
        writeln!(bw, "Case {t}").ok();
        let x = s.chars().next().unwrap();
        let y = s.chars().nth(2).unwrap();
        let n = it.next().unwrap().parse::<usize>().unwrap();
        for _ in 0..n {
            let s = it.next().unwrap();
            for c in s.chars() {
                let d = c.to_ascii_lowercase();
                let d = if d == x || d == y { '_' } else { c };
                write!(bw, "{d}").ok();
            }
            writeln!(bw).ok();
        }
        writeln!(bw).ok();
    }
}
