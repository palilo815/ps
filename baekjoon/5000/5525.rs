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
    let n = sc.read::<isize>();
    let m = sc.read::<usize>();
    let s = sc.raw().as_bytes();
    let mut ans = 0;
    let mut i = 0;
    while i != m {
        if s[i] == b'O' {
            i += 1;
            continue;
        }
        let mut j = i + 1;
        while j + 1 < m && s[j] == b'O' && s[j + 1] == b'I' {
            j += 2;
        }
        ans += 0.max(((j - i) / 2) as isize - n + 1);
        i = j;
    }
    writeln!(bw, "{ans}").ok();
}
