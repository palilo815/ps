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
    let n = sc.read::<usize>();
    let mut ans = 0;
    let mut one = 0;
    let mut two = 0;
    for c in sc.raw().bytes() {
        if c == b'1' {
            if one + two * 2 < n {
                one += 1;
            } else if two != 0 {
                two -= 1;
                one += 1;
            }
        } else if one + two * 2 < n - 1 {
            two += 1;
        }
        ans += one + two;
    }
    writeln!(bw, "{ans}").ok();
}
