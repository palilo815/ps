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
    let n = sc.read::<usize>() / 2;
    let h = sc.read::<usize>();
    let mut pref = vec![0; h];
    pref[0] = n as i32;
    for _ in 0..n {
        pref[sc.read::<usize>()] -= 1;
        pref[h - sc.read::<usize>()] += 1;
    }
    for i in 1..h {
        pref[i] += pref[i - 1];
    }
    let best = *pref.iter().min().unwrap();
    let count = pref.into_iter().filter(|&x| x == best).count();
    writeln!(bw, "{best} {count}").ok();
}
