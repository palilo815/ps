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
    let mut pref = (0..=n).map(|i| (0, i)).collect::<Vec<_>>();
    for i in 0..n {
        pref[i + 1].0 = pref[i].0 + sc.read::<i64>();
    }
    let q = sc.read::<usize>();
    let mut queries = (0..q)
        .map(|i| {
            let l = sc.read::<usize>() - 1;
            let r = sc.read::<usize>();
            let k = (r - l) / 3;
            (pref[l].0 + pref[r].0, l + k, r - k + 1, i)
        })
        .collect::<Vec<_>>();
    const INF: i64 = 0x3f3f3f3f3f3f3f3f;
    let mut ans = vec![INF; q];
    let mut seg = vec![!INF; n << 1];
    pref.pop();
    pref[0].0 = INF; // sentinel
    pref.sort_unstable_by(|l, r| l.0.cmp(&r.0));
    queries.sort_unstable_by(|l, r| l.0.cmp(&r.0));
    let mut it = 0;
    for &(sum, l, r, i) in queries.iter() {
        while pref[it].0 <= (sum >> 1) {
            let mut j = pref[it].1 + n;
            seg[j] = pref[it].0;
            while j != 1 {
                j >>= 1;
                seg[j] = std::cmp::max(seg[j << 1], seg[j << 1 | 1]);
            }
            it += 1;
        }
        let mut sl = l + n;
        let mut sr = r + n;
        let mut small = !INF;
        while sl != sr {
            if (sl & 1) == 1 {
                small = small.max(seg[sl]);
                sl += 1;
            }
            if (sr & 1) == 1 {
                sr -= 1;
                small = small.max(seg[sr]);
            }
            sl >>= 1;
            sr >>= 1;
        }
        ans[i] = ans[i].min(sum - small - small);
    }
    seg.fill(INF);
    pref[n - 1].0 = !INF; // sentinel
    pref[0..n - 1].reverse();
    queries.sort_unstable_by(|l, r| r.0.cmp(&l.0));
    let mut it = 0;
    for &(sum, l, r, i) in queries.iter() {
        while pref[it].0 > (sum >> 1) {
            let mut j = pref[it].1 + n;
            seg[j] = pref[it].0;
            while j != 1 {
                j >>= 1;
                seg[j] = std::cmp::min(seg[j << 1], seg[j << 1 | 1]);
            }
            it += 1;
        }
        let mut sl = l + n;
        let mut sr = r + n;
        let mut large = INF;
        while sl != sr {
            if (sl & 1) == 1 {
                large = large.min(seg[sl]);
                sl += 1;
            }
            if (sr & 1) == 1 {
                sr -= 1;
                large = large.min(seg[sr]);
            }
            sl >>= 1;
            sr >>= 1;
        }
        ans[i] = ans[i].min(large + large - sum);
    }
    for x in ans.into_iter() {
        writeln!(out, "{}", x).ok();
    }
}
