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
    let k = sc.read::<usize>();
    let n = sc.read::<usize>();
    let c = sc.read::<usize>();
    let mut edges = (0..k)
        .map(|_| {
            let mut u = sc.read::<usize>() - 1;
            let mut v = sc.read::<usize>() - 1;
            let w = sc.read::<usize>();
            if u > v {
                u = 2 * n - 2 - u;
                v = 2 * n - 2 - v;
            }
            (u, v, w)
        })
        .collect::<Vec<_>>();
    edges.sort_unstable();
    let mut bus = Vec::<usize>::with_capacity(c);
    let mut ans = 0;
    for (u, v, w) in edges {
        let i = bus.iter().position(|&x| x > u).unwrap_or(bus.len());
        ans += i;
        bus.drain(..i);
        let j = bus.iter().position(|&x| x > v).unwrap_or(bus.len());
        if c < bus.len() + w {
            bus.drain(j.max(c - w)..);
        }
        bus.splice(j..j, std::iter::repeat(v).take(w.min(c - bus.len())));
    }
    ans += bus.len();
    writeln!(bw, "{ans}").ok();
}
