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
    let mut a = [0; 6];
    let mut map = std::collections::HashMap::new();
    loop {
        map.clear();
        let mut x = sc.read::<usize>();
        let l = sc.read::<usize>();
        if x == 0 && l == 0 {
            break;
        }
        for i in 0.. {
            if let Some(j) = map.get(&x) {
                writeln!(bw, "{} {} {}", j, x, i - j).ok();
                break;
            }
            map.insert(x, i);
            let a = &mut a[..l];
            for d in a.iter_mut() {
                *d = x % 10;
                x /= 10;
            }
            a.sort_unstable();
            let mn = a.iter().fold(0, |acc, &x| acc * 10 + x);
            let mx = a.iter().rev().fold(0, |acc, &x| acc * 10 + x);
            x = mx - mn;
        }
    }
}
