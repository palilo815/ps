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
    let p = sc.read::<usize>() - 1;
    let mut v = (0..n).map(|_| (sc.read::<i32>(), sc.read::<i32>())).collect::<Vec<_>>();
    let mut cnt = 1;
    let mut fuel = v[p].0;
    v.swap_remove(p);
    v.retain(|x| x.0 >= x.1);
    v.sort_unstable_by(|l, r| l.1.cmp(&r.1));
    for (a, b) in v {
        if fuel < b {
            break;
        }
        cnt += 1;
        fuel += a - b;
    }
    writeln!(bw, "{fuel}\n{cnt}").ok();
}
