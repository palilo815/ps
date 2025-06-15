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
    loop {
        let s = sc.read::<String>();
        let m = sc.read::<i32>();
        if s == "#" {
            break;
        }
        let mut bus = sc.read::<i32>();
        let stop = sc.read::<usize>();
        for _ in 0..stop {
            let a = sc.read::<i32>();
            let b = sc.read::<i32>();
            bus = m.min(bus - a + b);
        }
        writeln!(bw, "{s} {bus}").ok();
    }
}
