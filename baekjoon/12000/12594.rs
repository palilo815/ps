use std::io::*;

struct Scanner {
    it: std::str::SplitAsciiWhitespace<'static>,
}

impl Scanner {
    fn new() -> Self {
        let mut buf = Vec::new();
        stdin().lock().read_to_end(&mut buf).ok();
        let s = unsafe { std::str::from_utf8_unchecked(Box::leak(buf.into_boxed_slice())) };
        Self { it: s.split_ascii_whitespace() }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    const N: usize = 1_000;
    let mut g = [0; N];
    let mut ord = [0; N];
    let mut euro = Vec::with_capacity(N);
    let t = sc.read::<usize>();
    for t in 1..=t {
        let r = sc.read::<usize>();
        let k = sc.read::<usize>();
        let n = sc.read::<usize>();
        let g = &mut g[..n];
        let ord = &mut ord[..n];
        euro.clear();
        g.fill_with(|| sc.read::<usize>());
        ord.fill(usize::MAX);
        let mut i = 0;
        while ord[i] == usize::MAX {
            ord[i] = euro.len();
            let mut acc = 0;
            for _ in 0..n {
                if acc + g[i] > k {
                    break;
                }
                acc += g[i];
                i = if i + 1 == n { 0 } else { i + 1 };
            }
            euro.push(acc);
        }
        let (non_cycle, cycle) = euro.split_at(ord[i]);
        let cycle_acc = cycle.iter().sum::<usize>();
        let ans = if r > non_cycle.len() {
            non_cycle.iter().sum::<usize>()
                + (r - non_cycle.len()) / cycle.len() * cycle_acc
                + cycle.iter().take((r - non_cycle.len()) % cycle.len()).sum::<usize>()
        } else {
            non_cycle.iter().take(r).sum::<usize>()
        };
        writeln!(bw, "Case #{t}: {ans}").ok();
    }
}
