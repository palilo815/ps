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
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let q = sc.read::<usize>();
    let mut buildings = (0..n).map(|_| (sc.read::<i32>(), sc.read::<i32>())).collect::<Vec<_>>();
    buildings.sort_unstable_by(|l, r| l.0.cmp(&r.0));
    buildings.dedup_by(|l, r| l.1 < r.1);
    let n = buildings.len();
    for _ in 0..q {
        let t = sc.read::<i32>();
        let i = buildings.partition_point(|x| x.0 + x.1 < t);
        let case1 = if i == 0 { 0 } else { buildings[i - 1].1 };
        let case2 = if i == n { 0 } else { t - buildings[i].0 };
        writeln!(out, "{}", case1.max(case2)).ok();
    }
}
