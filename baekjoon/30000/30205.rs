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
    let m = sc.read::<usize>();
    let mut p = sc.read::<i64>();
    let mut a = vec![0; m];
    for _ in 0..n {
        for x in a.iter_mut() {
            *x = sc.read::<i64>();
        }
        a.sort_unstable();
        let mut item = a.iter().position(|&x| x != -1).unwrap_or(m);
        for &x in a.iter().skip(item) {
            while x > p {
                if item == 0 {
                    writeln!(out, "0").ok();
                    return;
                }
                item -= 1;
                p *= 2;
            }
            p += x;
        }
        p *= 2_i64.pow(item as u32);
    }
    writeln!(out, "1").ok();
}
