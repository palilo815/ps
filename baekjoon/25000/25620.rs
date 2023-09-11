use std::io::*;

struct Scanner<'a> {
    it: std::str::SplitWhitespace<'a>,
}

impl<'a> Scanner<'a> {
    fn new(s: &'a str) -> Scanner<'a> {
        Scanner {
            it: s.split_whitespace(),
        }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
    }
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let q = sc.read::<usize>();
    let mut a = sc.read_vec::<u64>(n);
    let q = (0..q)
        .filter_map(|_| {
            let x = sc.read::<u64>();
            let y = sc.read::<u64>();
            if y == 1 {
                None
            } else {
                Some((x, y))
            }
        })
        .collect::<Vec<_>>();
    for s in a.iter_mut() {
        for &(x, y) in q.iter() {
            if *s == 0 || *s > 1_000_000_000 {
                break;
            }
            if *s <= x {
                *s *= y;
            }
        }
    }
    a.sort_unstable();
    for x in a.into_iter() {
        write!(out, "{x} ").ok();
    }
}
