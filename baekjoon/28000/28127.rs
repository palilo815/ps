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
        let a = sc.read::<i32>();
        let d = sc.read::<usize>();
        let mut x = sc.read::<i32>();
        for (floor, width) in (1..).zip((a..).step_by(d)) {
            if x <= width {
                writeln!(bw, "{floor} {x}").ok();
                break;
            }
            x -= width;
        }
    }
}
