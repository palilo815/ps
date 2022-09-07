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
    let mut intervals = (0..n)
        .map(|_| (sc.read::<i32>(), sc.read::<i32>(), sc.read::<i32>()))
        .collect::<Vec<_>>();
    intervals.sort_unstable_by(|l, r| l.0.cmp(&r.0).then(r.1.cmp(&l.1)));
    let mut pref = vec![(0, 0); n + 1];
    let mut m = 0;
    let mut rmax = i32::MIN;
    for (_, r, v) in intervals.into_iter() {
        if r > rmax {
            rmax = r;
            pref[m] = (r, pref[m].1 + v as i64);
            m += 1;
            pref[m].1 = -v as i64;
        } else {
            let i = pref[0..m].partition_point(|x| x.0 < r);
            pref[i].1 += v as i64;
            pref[m].1 -= v as i64;
        }
    }
    let ans = pref
        .iter()
        .take(m)
        .fold((0, 0), |(best, acc), x| {
            let acc = acc + x.1 as i64;
            (best.max(acc), acc)
        })
        .0;
    writeln!(out, "{}", ans).ok();
}
