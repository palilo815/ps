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
    loop {
        let n = sc.read::<i32>();
        if n == -1 {
            break;
        }
        let a = (1..n).filter(|&x| n % x == 0).collect::<Vec<_>>();
        let perfect = n == a.iter().sum::<i32>();
        write!(bw, "{n} ").ok();
        if perfect {
            write!(bw, "= {}", a[0]).ok();
            for x in a.into_iter().skip(1) {
                write!(bw, " + {x}").ok();
            }
        } else {
            write!(bw, "is NOT perfect.").ok();
        }
        writeln!(bw).ok();
    }
}
