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
}

struct FenwickTree<T> {
    size: usize,
    data: Box<[T]>,
}

impl<T> FenwickTree<T>
where
    T: Clone + Copy + std::ops::AddAssign + std::ops::Sub<Output = T> + std::cmp::PartialOrd,
{
    fn new(size: usize, e: T) -> Self {
        Self {
            size,
            data: vec![e; size + 1].into(),
        }
    }
    fn add(&mut self, mut i: usize, x: T) {
        assert!(i <= self.size);
        i += 1;
        while i <= self.size {
            self.data[i] += x;
            i += i & i.wrapping_neg();
        }
    }
    fn kth(&self, mut k: T) -> usize {
        let mut i = 0;
        for p in (0..(self.size).ilog2() + 1).rev() {
            let len = 1 << p;
            if i | len <= self.size && self.data[i | len] < k {
                i |= len;
                k = k - self.data[i];
            }
        }
        i
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let mut fw = FenwickTree::new(1_000_001, 0);
    for _ in 0..n {
        match sc.read::<char>() {
            '1' => {
                let i = fw.kth(sc.read::<i32>());
                fw.add(i, -1);
                writeln!(bw, "{i}").ok();
            }
            _ => {
                fw.add(sc.read::<usize>(), sc.read::<i32>());
            }
        }
    }
}
