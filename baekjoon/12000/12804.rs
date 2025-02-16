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
    let mut a = [0; 100];
    let mut b = [0; 100];
    let t = sc.read::<usize>();
    for _ in 0..t {
        let n = sc.read::<usize>();
        let m = sc.read::<usize>();
        let a = &mut a[..n];
        let b = &mut b[..m];
        a.iter_mut().for_each(|x| *x = sc.read());
        b.iter_mut().for_each(|x| *x = sc.read());
        a.sort_unstable();
        b.sort_unstable();
        let mut it = a.iter().rev();
        let mut jt = b.iter().peekable();
        let mut budget = 0;
        let mut ans = 0;
        for c in sc.read_bytes() {
            if c == b'+' {
                budget += it.next().unwrap();
            } else if budget >= **jt.peek().unwrap() {
                budget -= jt.next().unwrap();
            } else {
                ans += 1;
            }
        }
        writeln!(bw, "{ans}").ok();
    }
}
