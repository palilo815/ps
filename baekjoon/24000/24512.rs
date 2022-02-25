use std::io::Write;

#[allow(dead_code)]
mod scanner {
    use std::str::FromStr;
    pub struct Scanner<'a> {
        it: std::str::SplitWhitespace<'a>,
    }
    impl<'a> Scanner<'a> {
        pub fn new(s: &'a str) -> Scanner<'a> {
            Scanner {
                it: s.split_whitespace(),
            }
        }
        pub fn next<T: FromStr>(&mut self) -> T {
            self.it.next().unwrap().parse::<T>().ok().unwrap()
        }
        pub fn next_bytes(&mut self) -> Vec<u8> {
            self.it.next().unwrap().bytes().collect()
        }
        pub fn next_chars(&mut self) -> Vec<char> {
            self.it.next().unwrap().chars().collect()
        }
        pub fn next_vec<T: FromStr>(&mut self, len: usize) -> Vec<T> {
            (0..len).map(|_| self.next()).collect()
        }
    }
}

fn main() {
    use std::io::Read;
    let mut s = String::new();
    std::io::stdin().read_to_string(&mut s).unwrap();
    let mut sc = scanner::Scanner::new(&s);
    let out = std::io::stdout();
    let mut out = std::io::BufWriter::new(out.lock());
    run(&mut sc, &mut out);
}

trait ChMinMax {
    fn chmin(&mut self, x: Self) -> bool;
    fn chmax(&mut self, x: Self) -> bool;
}

impl<T: PartialOrd> ChMinMax for T {
    fn chmin(&mut self, x: Self) -> bool {
        *self > x && {
            *self = x;
            true
        }
    }
    fn chmax(&mut self, x: Self) -> bool {
        *self < x && {
            *self = x;
            true
        }
    }
}

fn next_permutation<T: std::cmp::Ord>(data: &mut [T]) -> bool {
    let i = match data.windows(2).rposition(|w| w[0] < w[1]) {
        Some(i) => i,
        None => {
            data.reverse();
            return false;
        }
    };
    let j = data.iter().rposition(|x| data[i] < *x).unwrap();
    data.swap(i, j);
    data[i + 1..].reverse();
    true
}

fn run<W: Write>(sc: &mut scanner::Scanner, out: &mut std::io::BufWriter<W>) {
    let n = sc.next::<usize>();
    let m = sc.next::<usize>();
    const INF: i32 = 100_000_000;
    let mut adj = [[INF; 9]; 9];
    for _ in 0..m {
        let u = sc.next::<usize>() - 1;
        let v = sc.next::<usize>() - 1;
        let w = sc.next::<i32>();
        adj[u][v] = w;
    }
    let mut ord = (0..n + 1)
        .map(|x| if x == n { 0 } else { x })
        .collect::<Vec<_>>();
    let mut ans = INF;
    let mut res = ord.clone();
    loop {
        if ans.chmin(ord.windows(2).fold(0, |acc, w| acc.max(adj[w[0]][w[1]]))) {
            res = ord.clone();
        }
        if !next_permutation(&mut ord[1..n]) {
            break;
        }
    }
    if ans == INF {
        writeln!(out, "-1").ok();
    } else {
        writeln!(out, "{}", ans).ok();
        for x in res.into_iter().skip(1) {
            write!(out, "{} ", x + 1).ok();
        }
    }
}
