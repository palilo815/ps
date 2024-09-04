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
    let k = sc.read::<usize>();
    let leaves = (0..n).map(|_| (sc.read::<i32>(), sc.read::<i32>())).collect::<Vec<_>>();
    let mut pref = vec![0; n + 1];
    let group = leaves
        .into_iter()
        .scan((usize::MAX, -1), |(id, rmax), (l, r)| {
            if *rmax < l {
                *id += 1;
                pref[*id] = l - *rmax;
            }
            *rmax = r.max(*rmax);
            Some(*id)
        })
        .collect::<Vec<_>>();
    for i in 0..n {
        pref[i + 1] += pref[i];
    }
    let mut ans = 0;
    let mut prv = 0;
    for _ in 0..k {
        let cur = group[sc.read::<usize>() - 1];
        ans += pref[prv].abs_diff(pref[cur]) as u64;
        prv = cur;
    }
    writeln!(bw, "{ans}").ok();
}
