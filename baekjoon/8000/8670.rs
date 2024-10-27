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
    let n = sc.read::<usize>();
    let mut i = 1;
    let mut ans = 0;
    while i <= n {
        let mut mn = usize::MAX;
        let mut mx = usize::MIN;
        for j in i.. {
            let x = sc.read::<usize>();
            mn = mn.min(x);
            mx = mx.max(x);
            if mn == i && mx == j {
                i = j + 1;
                ans += 1;
                break;
            }
        }
    }
    writeln!(bw, "{ans}").ok();
}
