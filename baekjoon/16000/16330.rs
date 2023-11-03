use std::io::*;

struct Scanner<'a> {
    it: std::str::SplitWhitespace<'a>,
}

impl<'a> Scanner<'a> {
    fn new(s: &str) -> Scanner {
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
    let m = sc.read::<usize>();
    let l = sc.read::<i32>();
    let fish = (0..n).map(|_| (sc.read::<i32>(), sc.read::<i32>())).collect::<Vec<_>>();
    let mut fishermen = (0..m).map(|i| (i, sc.read::<i32>())).collect::<Vec<_>>();
    fishermen.sort_unstable_by(|l, r| l.1.cmp(&r.1));
    let mut pref = vec![0; m + 1];
    for (x, y) in fish.into_iter().filter(|&(_, y)| y <= l) {
        let lo = fishermen.partition_point(|v| v.1 < x + y - l);
        let hi = fishermen.partition_point(|v| v.1 <= x - y + l);
        pref[lo] += 1;
        pref[hi] -= 1;
    }
    for i in 0..m {
        pref[i + 1] += pref[i];
    }
    let mut ans = vec![0; m];
    for (j, (i, _)) in fishermen.into_iter().enumerate() {
        ans[i] = pref[j];
    }
    for x in ans {
        writeln!(out, "{x}").ok();
    }
}
