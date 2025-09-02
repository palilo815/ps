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
    let a = sc.read::<i64>();
    let b = sc.read::<i64>();
    let points = (0..n).map(|_| (sc.read::<i64>(), sc.read::<i64>())).collect::<Vec<_>>();
    let mut ans = 0;
    for &(x1, _) in points.iter() {
        for &(_, y1) in points.iter() {
            let x2 = x1 + a;
            let y2 = y1 + b;
            let cnt = points.iter().filter(|&&(x, y)| x1 <= x && x <= x2 && y1 <= y && y <= y2).count();
            ans = ans.max(cnt);
        }
    }
    writeln!(bw, "{ans}").ok();
}
