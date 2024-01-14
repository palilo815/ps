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
    const N: usize = 50_000;
    let mut p = [true; N];
    p[0] = false;
    p[1] = false;
    for i in 2.. {
        if i * i >= N {
            break;
        }
        if p[i] {
            for q in p.iter_mut().skip(i * i).step_by(i) {
                *q = false;
            }
        }
    }
    let n = sc.read::<usize>();
    for (i, _) in p.into_iter().enumerate().filter(|x| x.1).take(n) {
        write!(out, "{i} ").ok();
    }
}
