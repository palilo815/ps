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
    fn read_array<const N: usize>(&mut self) -> [u8; N] {
        let s = self.it.next().unwrap();
        let mut a = [0; N];
        a[..s.len()].copy_from_slice(s.as_bytes());
        a
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let q = sc.read::<usize>();
    let mut map = std::collections::HashMap::new();
    let mut ans = 0;
    for _ in 0..q {
        let t = sc.read::<usize>();
        let s = sc.read_array::<15>();
        let pq = map.entry(s).or_insert(std::collections::BinaryHeap::new());
        match t {
            1 => {
                let k = sc.read::<usize>();
                pq.extend((0..k).map(|_| sc.read::<u32>()));
            }
            _ => {
                let k = sc.read::<usize>();
                for _ in 0..k.min(pq.len()) {
                    ans += pq.pop().unwrap() as u64;
                }
            }
        }
    }
    writeln!(bw, "{}", ans).ok();
}
