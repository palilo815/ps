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
    let mut balls = vec![vec![]; 2000];
    let n = sc.read::<usize>();
    for i in 0..n {
        let c = sc.read::<usize>() - 1;
        let s = sc.read::<usize>() - 1;
        balls[s].push((c, i));
    }
    let mut ans = vec![0; n];
    let mut sum_color = vec![0; n];
    let mut total = 0;
    for (s, arr) in (1..).zip(balls) {
        for &(c, i) in arr.iter() {
            ans[i] = total - sum_color[c];
        }
        total += s * arr.len();
        for (c, _) in arr {
            sum_color[c] += s;
        }
    }
    for x in ans {
        writeln!(bw, "{x}").ok();
    }
}
