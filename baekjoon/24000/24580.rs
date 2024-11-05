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
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let land = sc.read_vec::<u64>(n * m);
    let c0 = land.iter().filter(|&&x| x == 0).count();
    let c1 = land.iter().filter(|&&x| x == 1).count();
    let c2 = land.iter().filter(|&&x| x == 2).count();
    let ans = if c0 == 0 {
        (1u64 << ((c2 + 1) / 2)) - (1u64 << (c2 / 2))
    } else if c0 == 1 {
        if n == 1 || m == 1 {
            let first = *land.first().unwrap();
            let last = *land.last().unwrap();
            if first == 0 { u64::MAX } else { first }.min(if last == 0 { u64::MAX } else { last })
        } else if c1 == 0 {
            2
        } else {
            1
        }
    } else {
        0
    };
    writeln!(bw, "{ans}").ok();
}
