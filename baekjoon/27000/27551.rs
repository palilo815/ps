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

struct DynamicKth<T> {
    size: usize,
    data: Box<[T]>,
}

impl<T> DynamicKth<T>
where
    T: Clone + Copy + Default + std::ops::AddAssign + std::ops::SubAssign + std::cmp::PartialOrd,
{
    fn new(size: usize) -> Self {
        let size = size.next_power_of_two();
        Self {
            size,
            data: vec![T::default(); size + 1].into(),
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
        let mut len = self.size >> 1;
        while len != 0 {
            if self.data[i | len] < k {
                i |= len;
                k -= self.data[i];
            }
            len >>= 1;
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
    let mut dk = DynamicKth::new(val.len());
    let mut total = 0;
    for (a, v) in a {
        total += v;
        dk.add(a, v);
        writeln!(bw, "{}", val[dk.kth((total + 1) / 2)]).ok();
    }
}
