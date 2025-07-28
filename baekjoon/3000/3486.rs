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
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let t = sc.read::<usize>();
    for _ in 0..t {
        let a = sc.read::<String>();
        let b = sc.read::<String>();
        let a = a.chars().rev().collect::<String>().parse::<u32>().unwrap();
        let b = b.chars().rev().collect::<String>().parse::<u32>().unwrap();
        let c = (a + b).to_string();
        let c = c.chars().rev().collect::<String>().parse::<u32>().unwrap();
        writeln!(bw, "{c}").ok();
    }
}
