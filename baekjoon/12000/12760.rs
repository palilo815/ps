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
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let mut decks = (0..n).map(|_| sc.read_vec::<u32>(m)).collect::<Vec<_>>();
    decks.iter_mut().for_each(|v| v.sort_unstable());
    let mut scores = vec![0; n];
    for i in 0..m {
        let best = decks.iter().map(|v| v[i]).max().unwrap();
        for (score, deck) in scores.iter_mut().zip(decks.iter_mut()) {
            if deck[i] == best {
                *score += 1;
            }
        }
    }
    let best = *scores.iter().max().unwrap();
    for (i, score) in scores.into_iter().enumerate() {
        if score == best {
            write!(bw, "{} ", i + 1).ok();
        }
    }
}
