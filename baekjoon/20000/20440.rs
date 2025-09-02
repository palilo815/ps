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
    let mut s = vec![0; n];
    let mut t = vec![0; n];
    for i in 0..n {
        s[i] = sc.read::<i32>();
        t[i] = sc.read::<i32>();
    }
    s.sort_unstable();
    t.sort_unstable();
    let mut max = 0;
    let mut acc = 0;
    let mut start = 0;
    let mut range = (0, 0);
    let mut it = s.into_iter().peekable();
    let mut jt = t.into_iter().peekable();
    while it.peek().is_some() {
        match it.peek().unwrap().cmp(jt.peek().unwrap()) {
            std::cmp::Ordering::Less => {
                acc += 1;
                start = it.next().unwrap();
            }
            std::cmp::Ordering::Greater => {
                let end = jt.next().unwrap();
                if max < acc {
                    max = acc;
                    range = (start, end);
                }
                acc -= 1;
            }
            _ => {
                it.next();
                jt.next();
            }
        }
    }
    if max < acc {
        max = acc;
        range = (start, jt.next().unwrap());
    }
    writeln!(bw, "{max}").ok();
    writeln!(bw, "{} {}", range.0, range.1).ok();
}
