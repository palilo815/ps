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
    let n = sc.read::<usize>();
    let ban = (0..n)
        .map(|_| {
            let z = sc.read::<usize>();
            (0..z).fold(0, |mask, _| mask | 1 << (sc.read::<u32>() - 1))
        })
        .collect::<Vec<_>>();
    let ans = (0..1 << t).filter(|pizza| ban.iter().all(|ban| (pizza & ban) != *ban)).count();
    writeln!(bw, "{ans}").ok();
}
