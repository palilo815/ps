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
    let l = sc.read::<i32>();
    let t = sc.read::<i32>();
    let n = sc.read::<usize>();
    let mut a = (0..n)
        .map(|_| {
            let mut x = sc.read::<i32>();
            if sc.read::<char>() == 'L' {
                x = 2 * l - x;
            }
            x = (x + t) % (2 * l);
            if x < l {
                x
            } else {
                2 * l - x
            }
        })
        .collect::<Vec<_>>();
    a.sort_unstable();
    for x in a {
        write!(bw, "{x} ").ok();
    }
}
