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
    let mut k = sc.read::<usize>();
    let grid = sc.read_vec::<char>(n * m);
    let mut erased = vec![false; m];
    let mut ids = (0..m).collect::<Vec<_>>();
    for s in grid.chunks(m) {
        let mut sz = 1;
        'outer: for i in 1.. {
            let c = if i == ids.len() { char::default() } else { s[ids[i]] };
            while k != 0 && sz != 0 && s[ids[sz - 1]] > c {
                let num_gt = ids[..sz].iter().rev().take_while(|&&x| s[x] == s[ids[sz - 1]]).count();
                sz -= num_gt;
                if k < num_gt {
                    ids.drain(..sz);
                    sz = num_gt;
                    break 'outer;
                } else {
                    k -= num_gt;
                    ids[sz..sz + num_gt].iter().for_each(|&x| erased[x] = true);
                }
            }
            if i == ids.len() {
                break;
            }
            ids[sz] = ids[i];
            sz += 1;
        }
        ids.truncate(sz);
    }
    ids.into_iter().take(k).for_each(|x| erased[x] = true);
    for s in grid.chunks(m) {
        for (c, erased) in s.iter().zip(erased.iter()) {
            if !erased {
                write!(bw, "{c}").ok();
            }
        }
    }
}
