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
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let points = (0..n).map(|_| (sc.read::<i32>(), sc.read::<i32>())).collect::<Vec<_>>();
    let mut map = std::collections::HashMap::new();
    let mut ans = 0;
    for &(x0, y0) in points.iter() {
        map.clear();
        for &(x, y) in points.iter() {
            if x == x0 && y == y0 {
                continue;
            }
            let dx = x - x0;
            let dy = y - y0;
            let key = if dx == 0 {
                (0, 1)
            } else if dy == 0 {
                (1, 0)
            } else {
                let gcd = Numeric::gcd(dx.abs(), dy.abs());
                (dx / gcd, dy / gcd)
            };
            *map.entry(key).or_insert(0) += 1;
        }
        ans = ans.max(1 + *map.values().max().unwrap());
    }
    writeln!(bw, "{}", if ans < 3 { -1 } else { ans }).ok();
}
