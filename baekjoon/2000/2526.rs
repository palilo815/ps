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
    const P: usize = 97;
    let mut check = [0; P];
    let n = sc.read::<usize>();
    let p = sc.read::<usize>();
    let mut x = n % p;
    for i in 1.. {
        if check[x] != 0 {
            writeln!(bw, "{}", i - check[x]).ok();
            break;
        }
        check[x] = i;
        x = x * n % p;
    }
}
