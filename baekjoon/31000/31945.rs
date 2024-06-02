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
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let t = sc.read::<usize>();
    let mut a = [0; 4];
    for _ in 0..t {
        a.iter_mut().for_each(|x| *x = sc.read::<i32>());
        let and_sum = a.iter().fold(-1, std::ops::BitAnd::bitand);
        let or_sum = a.iter().fold(0, std::ops::BitOr::bitor);
        let yes = and_sum != 0 || or_sum != 7;
        writeln!(bw, "{}", if yes { "YES" } else { "NO" }).ok();
    }
}
