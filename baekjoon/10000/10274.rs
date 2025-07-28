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
    const N: usize = 1_000_000;
    let mut a = vec![0; N];
    let mut dq = std::collections::VecDeque::with_capacity(N);
    let t = sc.read::<usize>();
    for _ in 0..t {
        dq.clear();
        let n = sc.read::<usize>();
        let a = &mut a[..n];
        a.fill_with(|| sc.read::<i32>());
        let mut ans = 0;
        let mut pref = 0;
        dq.push_back((0, 0));
        for (&x, i) in a.iter().chain(a.iter()).zip(1..) {
            pref += x;
            while dq.front().is_some_and(|elem| elem.0 + n < i) {
                dq.pop_front();
            }
            ans = ans.max(pref - dq.front().unwrap().1);
            while dq.back().is_some_and(|elem| elem.1 >= pref) {
                dq.pop_back();
            }
            dq.push_back((i, pref));
        }
        writeln!(bw, "{ans}").ok();
    }
}
