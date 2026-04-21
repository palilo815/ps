use std::io::*;

struct Scanner {
    it: std::str::SplitAsciiWhitespace<'static>,
}

impl Scanner {
    fn new() -> Self {
        let mut buf = Vec::new();
        stdin().lock().read_to_end(&mut buf).ok();
        let s = unsafe { std::str::from_utf8_unchecked(Box::leak(buf.into_boxed_slice())) };
        Self { it: s.split_ascii_whitespace() }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let s = sc.read::<u32>();
    let t = sc.read::<u32>();
    if s == t {
        writeln!(bw, "0").ok();
        return;
    }
    let mut par = std::collections::HashMap::new();
    par.insert(s, u32::MAX);
    let mut dq = std::collections::VecDeque::new();
    dq.push_back(s);
    while let Some(u) = dq.pop_front() {
        if u == t {
            let mut ans = vec![];
            let mut u = u;
            while let Some(&p) = par.get(&u).filter(|&&v| v != u32::MAX) {
                let op = if p.checked_mul(p).is_some_and(|v| v == u) {
                    b'*'
                } else if p + p == u {
                    b'+'
                } else if u == 0 {
                    b'-'
                } else {
                    b'/'
                };
                ans.push(op);
                u = p;
            }
            ans.reverse();
            writeln!(bw, "{}", String::from_utf8(ans).unwrap()).ok();
            return;
        }
        let mut go = |u, v| {
            if let std::collections::hash_map::Entry::Vacant(e) = par.entry(v) {
                e.insert(u);
                dq.push_back(v);
            }
        };
        if u.checked_mul(u).is_some_and(|v| v <= t) {
            go(u, u * u)
        }
        if u + u <= t {
            go(u, u + u)
        }
        go(u, 0);
        go(u, 1);
    }
    writeln!(bw, "-1").ok();
}
