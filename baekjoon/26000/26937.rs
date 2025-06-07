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
    let m = sc.read::<usize>();
    let stores = (0..m)
        .map(|_| {
            let k = sc.read::<usize>();
            let w = sc.read::<u32>();
            let mut prices = vec![u32::MAX; n];
            for _ in 0..k {
                let i = sc.read::<usize>() - 1;
                prices[i] = sc.read::<u32>();
            }
            (w, prices)
        })
        .collect::<Vec<_>>();
    let mut ans = u32::MAX;
    let mut best = vec![0; n];
    for mask in 1..1 << m {
        best.fill(u32::MAX);
        let mut sum = 0;
        for (i, (w, prices)) in stores.iter().enumerate() {
            if mask >> i & 1 == 1 {
                sum += w;
                for (b, p) in best.iter_mut().zip(prices.iter()) {
                    *b = *p.min(b);
                }
            }
        }
        if best.iter().all(|&x| x != u32::MAX) {
            ans = ans.min(sum + best.iter().sum::<u32>());
        }
    }
    writeln!(bw, "{ans}").ok();
}
