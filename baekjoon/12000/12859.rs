use std::io::*;

struct Scanner {
    it: std::str::SplitAsciiWhitespace<'static>,
}

impl Scanner {
    fn new() -> Self {
        let mut s = String::new();
        stdin().read_to_string(&mut s).ok();
        Self {
            it: s.leak().split_ascii_whitespace(),
        }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
    }
}

trait Numeric {
    fn gcd(x: Self, y: Self) -> Self;
}

macro_rules! impl_numeric {
    ($($t:ty),*) => {
        $(impl Numeric for $t {
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
        }) *
    }
}

impl_numeric!(i32, i64, isize);
impl_numeric!(u32, u64, usize);

trait ChMinMax {
    fn chmin(&mut self, x: Self) -> bool;
}

impl<T: PartialOrd> ChMinMax for T {
    fn chmin(&mut self, x: Self) -> bool {
        *self > x && {
            *self = x;
            true
        }
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let l = sc.read_vec::<i32>(n);
    let c = sc.read_vec::<i32>(n);
    let mut map = std::collections::HashMap::new();
    let mut buf = vec![];
    for (l, c) in l.into_iter().zip(c) {
        buf.clear();
        for (&k, v) in map.iter() {
            buf.push((Numeric::gcd(l, k), c + v));
        }
        for &(l, c) in buf.iter() {
            map.entry(l).or_insert(i32::MAX).chmin(c);
        }
        map.entry(l).or_insert(i32::MAX).chmin(c);
    }
    writeln!(bw, "{}", map.get(&1).unwrap_or(&-1)).ok();
}
