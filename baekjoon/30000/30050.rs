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
    let q = sc.read::<usize>();
    let mut par = std::collections::HashMap::new();
    for _ in 0..q {
        if sc.read::<usize>() == 1 {
            let a = sc.read::<u32>();
            let b = sc.read::<u32>();
            par.insert(b, a);
        } else {
            let mut a = sc.read::<u32>();
            let mut b = sc.read::<u32>();
            let mut sum = 0;
            while a != b {
                if a > b {
                    std::mem::swap(&mut a, &mut b);
                }
                sum += b;
                b = *par.get(&b).unwrap_or(&(b / 2));
            }
            sum += a;
            writeln!(out, "{sum}").ok();
        }
    }
}
