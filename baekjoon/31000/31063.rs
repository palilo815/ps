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
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let mut h = sc.read_vec::<u64>(n);
    for _ in 0..m {
        let candy = sc.read::<u64>();
        let mut base = 0;
        for h in h.iter_mut() {
            if *h > base {
                let diff = candy.min(*h) - base;
                *h += diff;
                base += diff;
                if base == candy {
                    break;
                }
            }
        }
    }
    for h in h {
        writeln!(bw, "{h}").ok();
    }
}
