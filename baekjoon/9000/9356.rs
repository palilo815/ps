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

#[derive(Clone, Copy, Default, PartialEq, Eq)]
struct ModNum<const M: u32>(u32);

impl<const M: u32> ModNum<{ M }> {
    const fn new(v: u32) -> Self {
        Self(v % M)
    }
    const fn new_unchecked(v: u32) -> Self {
        Self(v)
    }
    const fn pow(&self, mut n: u64) -> Self {
        let mut r = 1;
        let mut a = self.0 as u64;
        while n != 0 {
            if n & 1 == 1 {
                r = r * a % M as u64;
            }
            a = a * a % M as u64;
            n >>= 1;
        }
        Self(r as u32)
    }
    const fn inv(&self) -> Self {
        assert!(self.0 != 0);
        self.pow(M as u64 - 2)
    }
    const fn neg(&self) -> Self {
        Self(if self.0 == 0 { 0 } else { M - self.0 })
    }
}

impl<const M: u32> std::ops::Add for ModNum<{ M }> {
    type Output = Self;
    fn add(self, rhs: Self) -> Self {
        let r = self.0 + rhs.0;
        Self(if r < M { r } else { r - M })
    }
}

impl<const M: u32> std::ops::Sub for ModNum<{ M }> {
    type Output = Self;
    fn sub(self, rhs: Self) -> Self {
        let r = self.0 - rhs.0 + M;
        Self(if r < M { r } else { r - M })
    }
}

impl<const M: u32> std::ops::Mul for ModNum<{ M }> {
    type Output = Self;
    fn mul(self, rhs: Self) -> Self {
        Self((self.0 as u64 * rhs.0 as u64 % M as u64) as u32)
    }
}

impl<const M: u32> std::ops::Div for ModNum<{ M }> {
    type Output = Self;
    fn div(self, rhs: Self) -> Self {
        self * rhs.inv()
    }
}

impl<const M: u32> std::ops::AddAssign for ModNum<{ M }> {
    fn add_assign(&mut self, rhs: Self) {
        *self = *self + rhs;
    }
}

impl<const M: u32> std::ops::SubAssign for ModNum<{ M }> {
    fn sub_assign(&mut self, rhs: Self) {
        *self = *self - rhs;
    }
}

impl<const M: u32> std::ops::MulAssign for ModNum<{ M }> {
    fn mul_assign(&mut self, rhs: Self) {
        *self = *self * rhs;
    }
}

impl<const M: u32> std::ops::DivAssign for ModNum<{ M }> {
    fn div_assign(&mut self, rhs: Self) {
        *self = *self / rhs;
    }
}

impl<const M: u32> std::fmt::Display for ModNum<{ M }> {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{}", self.0)
    }
}

impl<const M: u32> std::fmt::Debug for ModNum<{ M }> {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{}", self.0)
    }
}

impl<const M: u32> std::str::FromStr for ModNum<{ M }> {
    type Err = std::num::ParseIntError;
    fn from_str(s: &str) -> std::result::Result<Self, Self::Err> {
        let val = s.parse::<u32>()?;
        Ok(ModNum::new(val))
    }
}

type M = ModNum<1_000_000_007>;

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    const N: usize = 100_000;
    let mut fac = vec![M::default(); N + 10];
    fac[0] = M::new_unchecked(1);
    for i in 1..fac.len() {
        fac[i] = fac[i - 1] * M::new_unchecked(i as u32);
    }
    let t = sc.read::<usize>();
    for _ in 0..t {
        let n = sc.read::<usize>();
        writeln!(bw, "{}", fac[n + 9] / fac[9] / fac[n]).ok();
    }
}
