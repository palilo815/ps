use std::io::*;

struct Scanner<'a> {
    it: std::str::SplitWhitespace<'a>,
}

impl<'a> Scanner<'a> {
    fn new(s: &'a str) -> Scanner<'a> {
        Scanner {
            it: s.split_whitespace(),
        }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
    }
}

fn main() {
    let mut s = String::new();
    stdin().read_to_string(&mut s).unwrap();
    let mut sc = Scanner::new(&s);
    let out = stdout();
    let mut out = BufWriter::new(out.lock());
    run(&mut sc, &mut out);
}

fn run<W: Write>(sc: &mut Scanner, out: &mut BufWriter<W>) {
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let q = sc.read::<usize>();
    let hidden = (0..m)
        .map(|_| {
            let c = sc.read::<usize>();
            let p = sc.read_vec::<i32>(c);
            let w = sc.read_vec::<i32>(c);
            let b = sc.read::<i64>();
            (p, w, b)
        })
        .collect::<Vec<_>>();
    let output = sc.read_vec::<i32>(m);
    let mut offset = sc.read::<i64>();
    let mut coef = vec![0; n];
    for ((p, w, b), o) in hidden.into_iter().zip(output.into_iter()) {
        for (i, w) in p.into_iter().zip(w.into_iter()) {
            let i = i as usize - 1;
            coef[i] += w as i64 * o as i64;
        }
        offset += b * o as i64;
    }
    for _ in 0..q {
        let mut ans = offset;
        for c in coef.iter() {
            ans += sc.read::<i64>() * c;
        }
        writeln!(out, "{}", ans).ok();
    }
}
