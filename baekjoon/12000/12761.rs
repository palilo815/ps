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
    const N: usize = 100_000;
    let mut visited = [false; N + 1];
    let a = sc.read::<usize>();
    let b = sc.read::<usize>();
    let s = sc.read::<usize>();
    let t = sc.read::<usize>();
    let m = [a, b, a.wrapping_neg(), b.wrapping_neg(), usize::MAX, 1];
    let mut dq = std::collections::VecDeque::new();
    dq.push_back(s);
    visited[s] = true;
    for ans in 0.. {
        let len = dq.len();
        for _ in 0..len {
            let u = dq.pop_front().unwrap();
            if u == t {
                writeln!(bw, "{ans}").ok();
                return;
            }
            for &d in m.iter() {
                let v = u + d;
                if v <= N && !visited[v] {
                    visited[v] = true;
                    dq.push_back(v);
                }
            }
            for &d in m.iter().take(2) {
                let v = u * d;
                if v <= N && !visited[v] {
                    visited[v] = true;
                    dq.push_back(v);
                }
            }
        }
    }
}
