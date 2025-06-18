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
    let mut a = (0..n).map(|_| (sc.read::<i32>(), sc.read::<i32>())).collect::<Vec<_>>();
    a.sort_unstable_by(|l, r| l.0.cmp(&r.0));
    let dist = sc.read::<i32>();
    let mut fuel = sc.read::<i32>();
    let mut pq = std::collections::BinaryHeap::new();
    let mut i = 0;
    let mut stop = 0;
    while fuel < dist {
        while i != n && a[i].0 <= fuel {
            pq.push(a[i].1);
            i += 1;
        }
        if let Some(add) = pq.pop() {
            stop += 1;
            fuel += add;
        } else {
            writeln!(bw, "-1").ok();
            return;
        }
    }
    writeln!(bw, "{stop}").ok();
}
