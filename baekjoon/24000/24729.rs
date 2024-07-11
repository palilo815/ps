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
    const M: usize = 100_000;
    let mut a = [0; M + 1];
    let n = sc.read::<usize>();
    for _ in 0..n {
        a[sc.read::<usize>()] += 1;
    }
    for i in a.iter().position(|&x| x != 0).unwrap()..M {
        if a[i] <= 0 {
            break;
        }
        a[i + 1] -= a[i];
        a[i] = 0;
    }
    let ok = a.into_iter().all(|x| x == 0);
    writeln!(bw, "{}", if ok { 1 } else { -1 }).ok();
}
