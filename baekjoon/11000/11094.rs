use std::io::*;

struct Scanner {
    it: std::str::Split<'static, char>,
}

impl Scanner {
    fn new() -> Self {
        let mut s = String::new();
        stdin().read_to_string(&mut s).ok();
        Self { it: s.leak().split('\n') }
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
    const KEY: &str = "Simon says";
    let t = sc.read::<usize>();
    for _ in 0..t {
        let s = sc.raw();
        if s.starts_with(KEY) {
            writeln!(bw, "{}", s.chars().skip(10).collect::<String>()).ok();
        }
    }
}
