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
    fn read_bytes(&mut self) -> Vec<u8> {
        self.it.next().unwrap().bytes().collect()
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
    const fn new(x: u64) -> Self {
        Self(x)
    }
    const fn get(&self) -> u64 {
        if self.0 == u64::MAX {
            0
        } else {
            self.0
        }
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
    let needle = sc.read_bytes();
    let haystack = sc.read_bytes();
    if needle.len() > haystack.len() {
        writeln!(bw, "0").ok();
        return;
    }
    let cnt1 = needle.iter().fold([0; 26], |mut cnt, x| {
        cnt[(*x - b'a') as usize] += 1;
        cnt
    });
    let mut cnt2 = haystack.iter().take(needle.len()).fold([0; 26], |mut cnt, x| {
        cnt[(*x - b'a') as usize] += 1;
        cnt
    });
    const P: H = H::new(1996040009);
    let pn = (1..needle.len()).fold(H::new(1), |acc, _| acc * P);
    let mut h = haystack
        .iter()
        .take(needle.len())
        .fold(H::default(), |acc, &x| acc * P + H::new(x as u64));
    let mut set = std::collections::HashSet::with_hasher(ZeroHasher::default());
    if cnt1 == cnt2 {
        set.insert(h);
    }
    for i in needle.len()..haystack.len() {
        let c_in = haystack[i];
        let c_out = haystack[i - needle.len()];
        h = h - pn * H::new(c_out as u64);
        h = h * P + H::new(c_in as u64);
        cnt2[(c_in - b'a') as usize] += 1;
        cnt2[(c_out - b'a') as usize] -= 1;
        if cnt1 == cnt2 {
            set.insert(h);
        }
    }
    writeln!(bw, "{}", set.len()).ok();
}
