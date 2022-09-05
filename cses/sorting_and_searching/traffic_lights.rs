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
    let x = sc.read::<u32>();
    let n = sc.read::<usize>();
    let mut p = vec![0; n + 2];
    for p in p.iter_mut().skip(1).take(n) {
        *p = sc.read::<u32>();
    }
    p[n + 1] = x;
    let mut ids = (0..(n + 2)).collect::<Vec<_>>();
    ids.sort_unstable_by(|&lhs, &rhs| p[lhs].cmp(&p[rhs]));
    let mut prev = vec![0; n + 2];
    let mut next = vec![0; n + 2];
    for triple in ids.windows(3) {
        prev[triple[1]] = triple[0];
        next[triple[1]] = triple[2];
    }
    prev[ids[n + 1]] = ids[n];
    next[ids[0]] = ids[1];
    let mut ans = vec![0; n];
    ans[n - 1] = ids
        .windows(2)
        .fold(0, |mx, pair| mx.max(p[pair[1]] - p[pair[0]]));
    for i in (1..n).rev() {
        ans[i - 1] = ans[i].max(p[next[i + 1]] - p[prev[i + 1]]);
        prev[next[i + 1]] = prev[i + 1];
        next[prev[i + 1]] = next[i + 1];
    }
    for x in ans.into_iter() {
        write!(out, "{} ", x).ok();
    }
}
