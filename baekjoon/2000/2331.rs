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
    const N: usize = 300_000;
    let mut check = vec![0; N];
    let mut x = sc.read::<usize>();
    let p = sc.read::<u32>();
    for i in 1.. {
        if check[x] != 0 {
            writeln!(bw, "{}", check[x] - 1).ok();
            break;
        }
        check[x] = i;
        let mut y = 0;
        while x != 0 {
            y += (x % 10).pow(p);
            x /= 10;
        }
        x = y;
    }
}
