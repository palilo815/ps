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
    let points = (0..n).map(|_| (sc.read::<f64>(), sc.read::<f64>())).collect::<Vec<_>>();
    let m = sc.read::<usize>();
    let mut indice = [0; 17];
    for _ in 0..m {
        let p = sc.read::<usize>();
        let indice = &mut indice[..p];
        indice.fill_with(|| sc.read::<usize>());
        let ans = indice.windows(2).fold(0.0, |acc, w| {
            let u = points[w[0]];
            let v = points[w[1]];
            let dx = u.0 - v.0;
            let dy = u.1 - v.1;
            acc + (dx * dx + dy * dy).sqrt()
        });
        writeln!(bw, "{}", ans.round() as i64).ok();
    }
}

