use std::{collections::VecDeque, io::*};

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
    let c = sc.read_vec::<i32>(n);
    let mut ans = usize::MAX;
    let mut dq = VecDeque::new();
    for i in 0..n {
        let mut cost = 0;
        for j in 0..n {
            if c[(i + j) % n] != 0 {
                dq.push_back((i + j, c[(i + j) % n]));
            }
            if let Some((k, x)) = dq.front_mut() {
                cost += (i + j - *k) * (i + j - *k);
                *x -= 1;
                if *x == 0 {
                    dq.pop_front();
                }
            } else {
                cost = usize::MAX;
                break;
            }
        }
        ans = ans.min(cost);
    }
    writeln!(bw, "{ans}").ok();
}
