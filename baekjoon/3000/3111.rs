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
    fn raw(&mut self) -> &str {
        self.it.next().unwrap()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let a = sc.raw().bytes().collect::<Vec<_>>();
    let t = sc.raw().as_bytes();
    let k = a.len();
    let mut lstack = Vec::with_capacity(t.len());
    let mut rstack = Vec::with_capacity(t.len());
    let mut flag = true;
    let mut l = 0;
    let mut r = t.len();
    while l != r {
        if flag {
            lstack.push(t[l]);
            l += 1;
            if lstack.iter().rev().take(k).eq(a.iter().rev()) {
                lstack.truncate(lstack.len() - k);
                flag = false;
            }
        } else {
            r -= 1;
            rstack.push(t[r]);
            if rstack.iter().rev().take(k).eq(a.iter()) {
                rstack.truncate(rstack.len() - k);
                flag = true;
            }
        }
    }
    while let Some(c) = rstack.pop() {
        lstack.push(c);
        if lstack.iter().rev().take(k).eq(a.iter().rev()) {
            lstack.truncate(lstack.len() - k);
        }
    }
    writeln!(bw, "{}", String::from_utf8(lstack).unwrap()).ok();
}
