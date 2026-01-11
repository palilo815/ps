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
        let mut a = sc.read::<usize>();
        let b = sc.read::<usize>();
        let mut c = sc.read::<usize>() - 1;
        loop {
            let len = a.ilog10() + 1;
            let limit = 10_usize.pow(len);
            let count = (limit - a).div_ceil(b);
            let digits = count * len as usize;
            if c < digits {
                let i = c / len as usize;
                let j = c % len as usize;
                writeln!(bw, "{}", (a + i * b).to_string().chars().nth(j).unwrap()).ok();
                break;
            } else {
                c -= digits;
                a += count * b;
            }
        }
    }
}
