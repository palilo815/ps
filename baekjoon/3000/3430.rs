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
    const N: usize = 1_000_000;
    let z = sc.read::<usize>();
    let mut prev = vec![0; N];
    let mut ans = vec![0; N];
    let mut dsu = vec![0; N];
    for _ in 0..z {
        let n = sc.read::<usize>();
        let m = sc.read::<usize>();
        let prev = &mut prev[..n];
        let ans = &mut ans[..m];
        prev.fill(0);
        ans.fill(0);
        for i in 0..m {
            dsu[i] = i;
        }
        let mut ok = true;
        for i in 0..m {
            let t = sc.read::<usize>() - 1;
            if !ok {
                continue;
            }
            if t != usize::MAX {
                let mut x = std::mem::replace(&mut prev[t], i);
                while x != dsu[x] {
                    dsu[x] = dsu[dsu[x]];
                    x = dsu[x];
                }
                ok &= x != i;
                ans[i] = usize::MAX;
                ans[x] = t + 1;
                dsu[i] = i + 1;
                dsu[x] = x + 1;
            }
        }
        if ok {
            writeln!(out, "YES").ok();
            for x in ans.iter().filter(|&&x| x != usize::MAX) {
                write!(out, "{x} ").ok();
            }
            writeln!(out).ok();
        } else {
            writeln!(out, "NO").ok();
        }
    }
}
