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
    let mut i = 1;
    let mut lazy = (1, 0);
    for _ in 0..q {
        match sc.read::<usize>() {
            0 => lazy.1 += sc.read::<i64>(),
            1 => {
                let x = sc.read::<i64>();
                lazy.0 *= x;
                lazy.1 *= x;
            }
            2 => i += sc.read::<i64>(),
            _ => {
                writeln!(out, "{}", lazy.0 * i + lazy.1).ok();
            }
        }
    }
}
