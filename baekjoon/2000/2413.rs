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
    let mut a = sc.read_vec::<usize>(n);
    let mut idx = vec![0; n + 1];
    for (i, &x) in a.iter().enumerate() {
        idx[x] = i;
    }
    let mut used = vec![false; n + 1];
    used[0] = true;
    for i in 0..n {
        let x = a[i];
        if !used[x] && !used[x - 1] && idx[x] < idx[x - 1] {
            used[x] = true;
            used[x - 1] = true;
            a.swap(i, idx[x - 1]);
        }
    }
    for x in a {
        write!(out, "{x} ").ok();
    }
}
