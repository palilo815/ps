use std::io::Write;

struct Scanner<'a> {
    it: std::str::SplitWhitespace<'a>,
}

impl<'a> Scanner<'a> {
    fn new(s: &'a str) -> Scanner<'a> {
        Scanner {
            it: s.split_whitespace(),
        }
    }
    fn next<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
    fn next_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.next()).collect()
    }
}

fn run<W: Write>(sc: &mut Scanner, out: &mut std::io::BufWriter<W>) {
    let n = sc.next::<usize>();
    let m = sc.next::<usize>();
    let h = sc.next_vec::<i32>(n);
    let mut diff = vec![0; n + 1];
    for _ in 0..m {
        let l = sc.next::<usize>() - 1;
        let r = sc.next::<usize>();
        let k = sc.next::<i32>();
        diff[l] += k;
        diff[r] -= k;
    }
    for i in 0..n {
        diff[i + 1] += diff[i];
    }
    for (x, y) in h.into_iter().zip(diff.into_iter()) {
        write!(out, "{} ", x + y).ok();
    }
}

fn main() {
    use std::io::Read;
    let mut s = String::new();
    std::io::stdin().read_to_string(&mut s).unwrap();
    let mut sc = Scanner::new(&s);
    let out = std::io::stdout();
    let mut out = std::io::BufWriter::new(out.lock());
    run(&mut sc, &mut out);
}
