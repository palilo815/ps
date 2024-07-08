use std::io::*;

struct Scanner {
    it: std::str::SplitAsciiWhitespace<'static>,
}

impl Scanner {
    fn new() -> Self {
        let mut s = String::new();
        stdin().read_to_string(&mut s).ok();
        Self {
            it: s.leak().split_ascii_whitespace(),
        }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let mut pref = vec![0; n << 2 | 1];
    for x in pref.iter_mut().skip(2) {
        *x = sc.read::<u64>();
    }
    pref[1] = sc.read::<u64>();
    for i in 2..pref.len() {
        pref[i] += pref[i - 1];
    }
    let cycle = pref[n << 2];
    let mut station = [0; 4];
    station[1] = (0..3).map(|_| sc.read::<u64>()).min().unwrap();
    station[2] = (0..3).map(|_| sc.read::<u64>()).min().unwrap();
    station[3] = (0..3).map(|_| sc.read::<u64>()).min().unwrap();
    station[0] = (0..3).map(|_| sc.read::<u64>()).min().unwrap();
    let q = sc.read::<usize>();
    for _ in 0..q {
        let x = sc.read::<usize>();
        let d = (0..4)
            .map(|i| {
                let loc = pref[x];
                station[i] + loc.abs_diff(pref[i * n]).min(loc.abs_diff(pref[i * n] + cycle))
            })
            .min()
            .unwrap();
        writeln!(bw, "{d}").ok();
    }
}
