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
    let mut a = sc.read_vec::<i32>(n);
    let mut values = a.clone();
    values.sort_unstable();
    for x in a.iter_mut() {
        *x = values.partition_point(|v| v < x) as i32;
    }
    let mut ans = -1;
    let mut i = 0;
    while i != n {
        ans += 1;
        if i + 1 != n && a[i].abs_diff(a[i + 1]) == 1 {
            let d = a[i + 1] - a[i];
            i += 1;
            while i + 1 != n && a[i + 1] - a[i] == d {
                i += 1;
            }
        }
        i += 1;
    }
    writeln!(out, "{ans }").ok();
}
