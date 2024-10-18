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
    fn read_bytes(&mut self) -> Vec<u8> {
        self.it.next().unwrap().bytes().collect()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let k = sc.read::<usize>();
    let mut s = sc.read_bytes();
    let mut i = 0;
    let mut j = n - 1;
    for _ in 0..k {
        while i < n && s[i] == b'P' {
            i += 1;
        }
        while i < j && s[j] == b'C' {
            j -= 1;
        }
        if i >= j {
            break;
        }
        s.swap(i, j);
    }
    let mut p = 0_u64;
    let mut ans = 0;
    for c in s {
        if c == b'P' {
            p += 1;
        } else {
            ans += p * (p - 1) / 2;
        }
    }
    writeln!(bw, "{ans}").ok();
}
