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
    let a = sc.read_vec::<usize>(n);
    let mut sorted = a.clone();
    sorted.sort_unstable();
    let res = sorted.iter().enumerate().fold(0, |acc, (i, &x)| acc + (i + 1) * x);
    let mut pref = vec![0; n + 1];
    for i in 0..n {
        pref[i + 1] = pref[i] + sorted[i];
    }
    let q = sc.read::<usize>();
    for _ in 0..q {
        let old = a[sc.read::<usize>() - 1];
        let new = sc.read::<usize>();
        let old_i = sorted.partition_point(|&x| x < old);
        let new_i = sorted.partition_point(|&x| x < new);
        let mut res = res - (old_i + 1) * old;
        if old_i < new_i {
            res += new_i * new;
            res -= pref[new_i] - pref[old_i + 1];
        } else {
            res += (new_i + 1) * new;
            res += pref[old_i] - pref[new_i];
        }
        writeln!(out, "{res}").ok();
    }
}
