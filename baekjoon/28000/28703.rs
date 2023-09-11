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
    let mut a = sc.read_vec::<u32>(n);
    let mx = *a.iter().max().unwrap();
    a.iter_mut().for_each(|x| {
        while *x << 1 <= mx {
            *x <<= 1
        }
    });
    a.sort_unstable();
    let mut ans = a.last().unwrap() - a.first().unwrap();
    for w in a.windows(2) {
        ans = ans.min(w[0] * 2 - w[1]);
    }
    writeln!(out, "{ans}").ok();
}
