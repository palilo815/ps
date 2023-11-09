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
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let mut dist = vec![-1; n + 1];
    let mut q = std::collections::VecDeque::new();
    for _ in 0..m {
        let i = sc.read::<usize>();
        dist[i] = 0;
        q.push_back(i);
    }
    let mut d = 0;
    loop {
        let sz = q.len();
        for _ in 0..sz {
            let u = q.pop_front().unwrap();
            for p in 0..20 {
                let v = u ^ (1 << p);
                if v <= n && dist[v] == -1 {
                    dist[v] = d + 1;
                    q.push_back(v);
                }
            }
        }
        if q.is_empty() {
            break;
        }
        d += 1;
    }
    writeln!(out, "{d}").ok();
}
