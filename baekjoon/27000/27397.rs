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
    const M: usize = 52;
    let mut ranges = vec![vec![]; M];
    let index = |c: u8| (if c < b'a' { c - b'A' } else { c - b'a' + 26 }) as usize;
    let s = sc.raw().as_bytes();
    let mut i = 0;
    while i != s.len() {
        let mut j = i + 1;
        while j != s.len() && s[i] == s[j] {
            j += 1;
        }
        ranges[index(s[i])].push((i, j));
        i = j;
    }
    let mut ans = ranges.iter().flatten().map(|r| r.1 - r.0).max().unwrap();
    let n = sc.read::<usize>();
    for _ in 0..n {
        if sc.read::<char>() == '1' {
            let u = index(sc.read::<char>() as u8);
            let v = index(sc.read::<char>() as u8);
            if ranges[u].is_empty() {
                continue;
            }
            if ranges[v].is_empty() {
                ranges.swap(u, v);
                continue;
            }
            let a = std::mem::take(&mut ranges[u]);
            let b = std::mem::take(&mut ranges[v]);
            let mut c = Vec::<(usize, usize)>::with_capacity(a.len() + b.len());
            let mut it = a.into_iter().peekable();
            let mut jt = b.into_iter().peekable();
            loop {
                let x = match (it.peek(), jt.peek()) {
                    (Some((x, _)), Some((y, _))) => {
                        if x < y {
                            it.next()
                        } else {
                            jt.next()
                        }
                    }
                    (Some(_), None) => it.next(),
                    (None, Some(_)) => jt.next(),
                    (None, None) => break,
                }
                .unwrap();
                if c.last().is_some_and(|y| y.1 == x.0) {
                    c.last_mut().unwrap().1 = x.1;
                } else {
                    c.push(x);
                }
            }
            ans = ans.max(c.iter().map(|r| r.1 - r.0).max().unwrap());
            ranges[v] = c;
        } else {
            writeln!(bw, "{ans}").ok();
        }
    }
}
