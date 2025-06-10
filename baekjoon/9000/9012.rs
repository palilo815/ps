use std::io::*;

struct Scanner {
    it: std::str::SplitAsciiWhitespace<'static>,
}

impl Scanner {
    fn new() -> Self {
        let mut s = String::new();
        stdin().read_to_string(&mut s).ok();
        Self { it: s.leak().split_ascii_whitespace() }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
    fn raw(&mut self) -> &str {
        self.it.next().unwrap()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let t = sc.read::<usize>();
    for _ in 0..t {
        let mut acc = 0;
        for c in sc.raw().bytes() {
            match c {
                b'(' => acc += 1,
                _ => {
                    acc -= 1;
                    if acc == -1 {
                        break;
                    }
                }
            }
        }
        writeln!(bw, "{}", if acc == 0 { "YES" } else { "NO" }).ok();
    }
}
