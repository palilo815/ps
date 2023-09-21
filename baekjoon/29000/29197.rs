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
    let mut set = std::collections::HashSet::new();
    for _ in 0..n {
        let x = sc.read::<i32>();
        let y = sc.read::<i32>();
        let gcd = Numeric::gcd(x.abs(), y.abs());
        set.insert((x / gcd, y / gcd));
    }
    writeln!(out, "{}", set.len()).ok();
}
