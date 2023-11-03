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
    let m = sc.read::<u32>();
    let a = std::iter::once(0).chain((0..n).map(|_| sc.read::<u32>())).collect::<Vec<_>>();
    let n = n + 1;
    let mut b = vec![0; n * n];
    for i in 0..n {
        for j in 0..n {
            b[i * n + j] = a[i] + a[j];
        }
    }
    b.retain(|&x| x <= m);
    b.sort_unstable();
    let mut ans = 0;
    let mut j = b.len() - 1;
    for i in 0..b.len() {
        while i <= j && b[i] + b[j] > m {
            j -= 1;
        }
        if i > j {
            break;
        }
        ans = ans.max(b[i] + b[j]);
    }
    writeln!(out, "{ans}").ok();
}
