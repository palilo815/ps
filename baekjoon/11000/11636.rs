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
        let mut ans = 0;
        let mut prv = sc.read::<i32>();
        loop {
            let cur = sc.read::<i32>();
            if cur == 0 {
                break;
            }
            ans += 0.max(cur - prv * 2);
            prv = cur;
        }
        writeln!(bw, "{ans}").ok();
    }
}
