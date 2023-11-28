use std::io::*;

struct Scanner<'a> {
    it: std::str::SplitWhitespace<'a>,
}

impl<'a> Scanner<'a> {
    fn new(s: &str) -> Scanner {
        Scanner {
            it: s.split_whitespace(),
        }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let parity = (0..n).map(|_| (sc.read::<i32>() + sc.read::<i32>()) & 1).collect::<Vec<_>>();
    let odd = parity.iter().sum::<i32>();
    if odd == 0 || odd == n as i32 {
        writeln!(out, "NO").ok();
        return;
    }
    writeln!(out, "YES").ok();
    for (i, &p) in parity.iter().enumerate() {
        if p == 0 {
            write!(out, "{} ", i + 1).ok();
        }
    }
    for (i, &p) in parity.iter().enumerate() {
        if p == 1 {
            write!(out, "{} ", i + 1).ok();
        }
    }
}
