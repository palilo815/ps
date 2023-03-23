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
    let k = sc.read::<u32>();
    let q = sc.read::<usize>();
    let a = sc.read_vec::<u32>(n);
    let mut acc = 0;
    let mut prv = usize::MAX;
    let mut i = 0;
    for _ in 0..q {
        let x = sc.read::<usize>();
        while i != x {
            if a[i] == k {
                prv = i;
            }
            acc += i - prv;
            i += 1;
        }
        writeln!(out, "{acc}").ok();
    }
}
