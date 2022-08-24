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
    let n = sc.read::<usize>();
    let mut intervals = std::collections::HashSet::new();
    let mut l_to = std::collections::HashMap::<u32, u32>::new();
    let mut r_to = std::collections::HashMap::<u32, u32>::new();
    for _ in 0..n {
        let l = sc.read::<u32>();
        let r = sc.read::<u32>();
        intervals.insert((l, r));
        let x = l_to.entry(l).or_insert(u32::MIN);
        *x = r.max(*x);
        let x = r_to.entry(r).or_insert(u32::MAX);
        *x = l.min(*x);
    }
    let n = sc.read::<usize>();
    for _ in 0..n {
        let l = sc.read::<u32>();
        let r = sc.read::<u32>();
        let ans = if intervals.contains(&(l, r)) {
            1
        } else if *l_to.get(&l).unwrap_or(&0) >= r && *r_to.get(&r).unwrap_or(&u32::MAX) <= l {
            2
        } else {
            -1
        };
        writeln!(out, "{}", ans).ok();
    }
}
