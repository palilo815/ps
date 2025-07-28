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
    let t = sc.read::<usize>();
    for _ in 0..t {
        let n = sc.read::<usize>();
        let req_x = sc.read::<i32>();
        let req_y = sc.read::<i32>();
        let mut y = 0;
        let mut price_x = i32::MAX;
        let mut price_y = i32::MAX;
        let mut ans = 0;
        for _ in 0..n {
            let c = sc.read::<i32>();
            price_x = price_x.min(sc.read::<i32>());
            price_y = price_y.min(sc.read::<i32>());
            y -= req_y * c;
            ans += price_x * c * req_x;
            if y < 0 {
                let buy = (79 - y) / 80;
                ans += price_y * buy;
                y += 80 * buy
            }
        }
        writeln!(bw, "{ans}").ok();
    }
}
