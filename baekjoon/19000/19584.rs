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
}

fn run<W: Write>(sc: &mut Scanner, out: &mut std::io::BufWriter<W>) {
    let n = sc.next::<usize>();
    let m = sc.next::<usize>();
    let a = (0..n)
        .map(|_| {
            sc.next::<i32>();
            sc.next::<i32>()
        })
        .collect::<Vec<_>>();
    let mut ins = vec![(0, 0); m];
    let mut rem = vec![(0, 0); m];
    for i in 0..m {
        let mut u = a[sc.next::<usize>() - 1];
        let mut v = a[sc.next::<usize>() - 1];
        let w = sc.next::<u32>();
        if u > v {
            std::mem::swap(&mut u, &mut v);
        }
        ins[i] = (u, w);
        rem[i] = (v, w);
    }
    ins.sort_unstable_by(|lhs, rhs| lhs.0.cmp(&rhs.0));
    rem.sort_unstable_by(|lhs, rhs| lhs.0.cmp(&rhs.0));
    let (mut i, mut j, mut res, mut ans) = (0, 0, 0, 0);
    while i != m {
        if ins[i].0 > rem[j].0 {
            res -= rem[j].1 as u64;
            j += 1;
        } else {
            res += ins[i].1 as u64;
            ans = ans.max(res);
            i += 1;
        }
    }
    writeln!(out, "{}", ans).ok();
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
