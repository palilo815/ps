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

struct DisjointSet {
    pub p: Box<[i32]>,
}

impl DisjointSet {
    fn new(n: usize) -> Self {
        Self {
            p: vec![-1; n].into_boxed_slice(),
        }
    }
    fn find(&mut self, u: usize) -> usize {
        if self.p[u] < 0 {
            u
        } else {
            let rt = self.find(self.p[u] as usize);
            self.p[u] = rt as i32;
            rt
        }
    }
}

trait Numeric {
    fn gcd(x: Self, y: Self) -> Self;
    fn lcm(x: Self, y: Self) -> Self;
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
            fn lcm(u: Self, v: Self) -> Self {
                u / Self::gcd(u, v) * v
            }
        }) *
    }
}

impl_numeric!(i8, i16, i32, i64, i128, isize);
impl_numeric!(u8, u16, u32, u64, u128, usize);

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let mut dsu = DisjointSet::new(n);
    let mut sum = n;
    let mut compo = n;
    for _ in 0..m {
        if sc.read::<usize>() == 1 {
            let u = dsu.find(sc.read::<usize>() - 1);
            let v = dsu.find(sc.read::<usize>() - 1);
            if u != v {
                compo -= 1;
                sum -= -dsu.p[u] as usize * -dsu.p[u] as usize;
                sum -= -dsu.p[v] as usize * -dsu.p[v] as usize;
                dsu.p[u] += dsu.p[v];
                dsu.p[v] = u as i32;
                sum += -dsu.p[u] as usize * -dsu.p[u] as usize;
            }
        } else {
            let g = Numeric::gcd(sum, compo);
            writeln!(out, "{}/{}", sum / g, compo / g).ok();
        }
    }
}
