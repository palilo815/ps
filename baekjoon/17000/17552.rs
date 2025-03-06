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
    let mut a = sc.read_vec::<i32>(1 << n);
    a.sort_unstable();
    let mut deleted = std::collections::BinaryHeap::with_capacity(1 << n);
    let mut revealed = vec![];
    deleted.push(std::cmp::Reverse(0));
    for x in a {
        if deleted.peek() == Some(&std::cmp::Reverse(x)) {
            deleted.pop();
        } else if revealed.len() == n {
            writeln!(bw, "impossible").ok();
            return;
        } else {
            for i in 1..1 << revealed.len() {
                let mut acc = x;
                for (j, &y) in revealed.iter().enumerate() {
                    if (i >> j) & 1 == 1 {
                        acc += y;
                    }
                }
                deleted.push(std::cmp::Reverse(acc));
            }
            revealed.push(x);
        }
    }
    assert!(deleted.is_empty());
    revealed.sort_unstable();
    for x in revealed {
        writeln!(bw, "{x}").ok();
    }
}
