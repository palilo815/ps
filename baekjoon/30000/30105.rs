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
    let a = (0..n).map(|_| sc.read::<i32>()).chain(std::iter::once(i32::MAX)).collect::<Vec<_>>();
    let ok = |d: i32| -> bool {
        let mut l = 0;
        let mut r = 0;
        for &x in a.iter().take(n) {
            while a[l] < x - d {
                l += 1;
            }
            while a[r] < x + d {
                r += 1;
            }
            if a[l] != x - d && a[r] != x + d {
                return false;
            }
        }
        true
    };
    let ans = a
        .iter()
        .skip(1)
        .take(n - 1)
        .filter_map(|&x| {
            let d = x - a[0];
            if ok(d) {
                Some(d)
            } else {
                None
            }
        })
        .collect::<Vec<_>>();
    writeln!(out, "{}", ans.len()).ok();
    for x in ans {
        write!(out, "{x} ").ok();
    }
}
