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

#[derive(Clone, Copy, PartialEq)]
enum Colour {
    White,
    Grey,
    Black,
}

use Colour::*;

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    const N: usize = 100_000;
    let mut a = [0; N];
    let mut colour = [White; N];
    let t = sc.read::<usize>();
    for _ in 0..t {
        let n = sc.read::<usize>();
        let a = &mut a[..n];
        let colour = &mut colour[..n];
        for x in a.iter_mut() {
            *x = sc.read::<usize>() - 1;
        }
        colour.fill(White);
        let mut cycle = 0;
        for i in 0..n {
            if colour[i] == Black {
                continue;
            }
            let mut u = i;
            while colour[u] == White {
                colour[u] = Grey;
                u = a[u];
            }
            while colour[u] == Grey {
                colour[u] = Black;
                u = a[u];
                cycle += 1;
            }
            u = i;
            while colour[u] == Grey {
                colour[u] = Black;
                u = a[u];
            }
        }
        writeln!(out, "{}", n - cycle).ok();
    }
}
