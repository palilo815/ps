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
    const N: usize = 1_000;
    let mut a = vec![String::new(); N];
    loop {
        let n = sc.read::<usize>();
        if n == 0 {
            break;
        }
        let a = &mut a[..n];
        a.fill_with(|| sc.read::<String>());
        for (l, r) in a.iter().zip(a.iter().skip(n.div_ceil(2))) {
            writeln!(bw, "{l}\n{r}").ok();
        }
        if n & 1 == 1 {
            writeln!(bw, "{}", a[n / 2]).ok();
        }
    }
}
