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
    let _ = sc.read::<u32>();
    let q = sc.read::<usize>();
    let mut has = [false; 1 << 20];
    for _ in 0..q {
        let x = sc.read::<usize>();
        let mut i = x;
        let mut blocked = 0;
        while i != 1 {
            if has[i] {
                blocked = i;
            }
            i >>= 1;
        }
        if blocked == 0 {
            has[x] = true;
        }
        writeln!(bw, "{}", blocked).ok();
    }
}
