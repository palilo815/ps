use std::io::*;

struct Scanner<'a> {
    it: std::str::SplitWhitespace<'a>,
}

impl<'a> Scanner<'a> {
    fn new(s: &str) -> Scanner {
        Scanner {
            it: s.split_whitespace(),
        }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
    fn read_bytes(&mut self) -> Vec<u8> {
        self.it.next().unwrap().bytes().collect()
    }
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let mut s = (0..n).map(|_| sc.read_bytes()).collect::<Vec<_>>();
    let mut next = vec![usize::MAX; n];
    let mut last = (0..n).collect::<Vec<_>>();
    let mut first = match n & 3 {
        0 => 0,
        1 => n - 1,
        2 => 1,
        _ => n,
    };
    for _ in 1..n {
        let u = sc.read::<usize>() - 1;
        let v = sc.read::<usize>() - 1;
        first ^= v;
        next[last[u]] = v;
        last[u] = last[v];
    }
    while first != usize::MAX {
        write!(out, "{}", String::from_utf8(std::mem::take(&mut s[first])).unwrap()).ok();
        first = next[first];
    }
}
