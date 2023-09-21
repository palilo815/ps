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
    let q = sc.read::<usize>();
    let mut p = vec![usize::MAX; n + 2];
    let mut color = vec![0; n + 1];
    for _ in 0..q {
        let l = sc.read::<usize>();
        let r = sc.read::<usize>();
        let x = sc.read::<u32>();
        let mut i = l;
        loop {
            while p[i] != usize::MAX {
                if p[p[i]] != usize::MAX {
                    p[i] = p[p[i]];
                }
                i = p[i];
            }
            if i > r {
                break;
            }
            color[i] = x;
            p[i] = i + 1;
        }
    }
    for x in color.into_iter().skip(1) {
        write!(out, "{x} ").ok();
    }
}
