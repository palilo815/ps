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
    let mut a = (0..n).map(|_| (sc.read::<usize>(), sc.read::<usize>())).collect::<Vec<_>>();
    let mut val = a.iter().map(|x| x.0).collect::<Vec<_>>();
    val.sort_unstable();
    val.dedup();
    a.iter_mut().for_each(|x| x.0 = val.partition_point(|&v| v < x.0));
    let mut fw = FenwickTree::new(val.len(), 0);
    let mut total = 0;
    for (a, v) in a {
        total += v;
        fw.add(a, v);
        writeln!(bw, "{}", val[fw.kth((total + 1) / 2)]).ok();
    }
}
