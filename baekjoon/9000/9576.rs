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
    const N: usize = 1000;
    let mut a = [(0, 0); N];
    let mut v = [false; N];
    let t = sc.read::<usize>();
    for _ in 0..t {
        let n = sc.read::<usize>();
        let m = sc.read::<usize>();
        let a = &mut a[..m];
        let v = &mut v[..n];
        a.fill_with(|| (sc.read::<usize>() - 1, sc.read::<usize>()));
        a.sort_unstable_by(|l, r| l.1.cmp(&r.1).then(l.0.cmp(&r.0)));
        v.fill(false);
        for &(l, r) in a.iter() {
            let v = &mut v[l..r];
            if let Some(i) = v.iter().position(|&x| !x) {
                v[i] = true;
            }
        }
        let ans = v.iter().filter(|&&x| x).count();
        writeln!(bw, "{ans}").ok();
    }
}
