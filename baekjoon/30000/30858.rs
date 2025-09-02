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
    fn raw(&mut self) -> &str {
        self.it.next().unwrap()
    }
}

#[derive(Clone, Copy, Default)]
struct ZeroHasher(u64);

impl std::hash::Hasher for ZeroHasher {
    fn write_u64(&mut self, i: u64) {
        self.0 = i;
    }
    fn write(&mut self, _: &[u8]) {
        unimplemented!()
    }
    fn finish(&self) -> u64 {
        self.0
    }
}

impl std::hash::BuildHasher for ZeroHasher {
    type Hasher = Self;
    fn build_hasher(&self) -> Self::Hasher {
        Self::default()
    }
}

#[derive(Clone, Copy, Debug, Default)]
struct H(u64);

impl H {
    const fn get(&self) -> u64 {
        if self.0 == u64::MAX { 0 } else { self.0 }
    }
}

impl std::ops::Add for H {
    type Output = H;
    fn add(self, rhs: Self) -> Self::Output {
        let (r, flow) = self.0.overflowing_add(rhs.0);
        H(r + flow as u64)
    }
}

impl std::ops::Sub for H {
    type Output = H;
    fn sub(self, rhs: Self) -> Self::Output {
        let (r, flow) = self.0.overflowing_sub(rhs.0);
        H(r - flow as u64)
    }
}

impl std::ops::Mul for H {
    type Output = H;
    fn mul(self, rhs: Self) -> Self::Output {
        let r = self.0 as u128 * rhs.0 as u128;
        H(r as u64) + H((r >> 64) as u64)
    }
}

impl std::cmp::PartialEq for H {
    fn eq(&self, other: &Self) -> bool {
        self.get() == other.get()
    }
}

impl std::cmp::Eq for H {}

impl std::cmp::Ord for H {
    fn cmp(&self, other: &Self) -> std::cmp::Ordering {
        self.get().cmp(&other.get())
    }
}

impl std::cmp::PartialOrd for H {
    fn partial_cmp(&self, other: &Self) -> Option<std::cmp::Ordering> {
        Some(self.cmp(other))
    }
}

impl std::fmt::Display for H {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{}", self.get())
    }
}

impl std::hash::Hash for H {
    fn hash<H: std::hash::Hasher>(&self, state: &mut H) {
        state.write_u64(self.get())
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let k = sc.read::<usize>();
    let m = sc.read::<usize>();
    let f = sc.read::<usize>();
    let mut hash_values = vec![H(0); n + 1];
    let powers = (0..k)
        .scan(H(1), |acc, _| {
            *acc = *acc * H(101);
            Some(*acc)
        })
        .collect::<Vec<_>>();
    for &p in powers.iter() {
        let card = (0..m).map(|_| sc.read::<usize>()).collect::<std::collections::HashSet<_>>();
        for num in card {
            hash_values[num] = hash_values[num] + p;
        }
    }
    let mut map = std::collections::HashMap::with_hasher(ZeroHasher::default());
    for (num, h) in hash_values.into_iter().enumerate().skip(1) {
        if map.insert(h, num).is_some() {
            map.insert(h, 0);
        }
    }
    for _ in 0..f {
        let answer = sc.raw().bytes();
        let h = powers.iter().zip(answer).filter(|(_, x)| *x == b'Y').fold(H(0), |acc, x| acc + *x.0);
        writeln!(bw, "{}", map.get(&h).unwrap()).ok();
    }
}
