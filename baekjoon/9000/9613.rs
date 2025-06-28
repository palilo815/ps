use std::io::*;

struct Scanner {
    it: std::str::SplitAsciiWhitespace<'static>,
}

impl Scanner {
    fn new() -> Self {
        let mut s = String::new();
        stdin().read_to_string(&mut s).ok();
        Self { it: s.leak().split_ascii_whitespace() }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
}

trait Gcd {
    fn gcd(x: Self, y: Self) -> Self;
    fn lcm(x: Self, y: Self) -> Self;
}

macro_rules! impl_gcd {
    ($t: ty) => {
        impl Gcd for $t {
            fn gcd(mut u: Self, mut v: Self) -> Self {
                if u == 0 || v == 0 {
                    return u | v;
                }
                let k = {
                    let i = u.trailing_zeros();
                    let j = v.trailing_zeros();
                    u >>= i;
                    v >>= j;
                    i.min(j)
                };
                loop {
                    if u > v {
                        std::mem::swap(&mut u, &mut v);
                    }
                    v -= u;
                    if v == 0 {
                        return u << k;
                    }
                    v >>= v.trailing_zeros();
                }
            }
            fn lcm(u: Self, v: Self) -> Self {
                u / Self::gcd(u, v) * v
            }
        }
    };
}

impl_gcd!(u64);

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    const N: usize = 100;
    let mut a = [0; N];
    let t = sc.read::<usize>();
    for _ in 0..t {
        let n = sc.read::<usize>();
        let a = &mut a[..n];
        a.fill_with(|| sc.read::<u64>());
        let mut ans = 0;
        for i in 0..n {
            for j in 0..i {
                ans += u64::gcd(a[i], a[j]);
            }
        }
        writeln!(bw, "{ans}").ok();
    }
}
