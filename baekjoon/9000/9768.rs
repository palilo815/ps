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
    const M: usize = 10;
    const K: usize = 1_000_000;
    let mut deck = (0..M).map(|_| Vec::with_capacity(K)).collect::<Vec<_>>();
    let t = sc.read::<usize>();
    for _ in 0..t {
        let _ = sc.read::<usize>();
        let m = sc.read::<usize>();
        let k = sc.read::<usize>();
        let deck = &mut deck[..m];
        deck.iter_mut().for_each(|v| v.clear());
        for _ in 0..k {
            let rank = sc.read::<u32>();
            let suit = sc.read::<usize>() - 1;
            deck[suit].push(rank);
        }
        let mut ans = 1;
        for v in deck {
            v.sort_unstable();
            v.dedup();
            let mut i = 0;
            while i != v.len() {
                let mut j = i + 1;
                while j != v.len() && v[j] == v[j - 1] + 1 {
                    j += 1;
                }
                ans = ans.max(j - i);
                i = j;
            }
        }
        writeln!(bw, "{}", if ans == 1 { 0 } else { ans }).ok();
    }
}
