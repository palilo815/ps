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
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
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

impl_gcd!(u32);

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let a = sc.read_vec::<u32>(n);
    let gcd = a.iter().fold(0, |g, &x| u32::gcd(g, x));
    let mut pq = a
        .into_iter()
        .map(|x| std::cmp::Reverse((x / gcd).trailing_zeros()))
        .collect::<std::collections::BinaryHeap<_>>();
    while pq.len() != 1 {
        let x = pq.pop().unwrap();
        let y = pq.peek().unwrap();
        let z = x.0.min(y.0) + 1;
        pq.peek_mut().unwrap().0 = z;
    }
    writeln!(bw, "{}", gcd as u64 * (1_u64 << pq.pop().unwrap().0)).ok();
}
