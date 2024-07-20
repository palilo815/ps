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

struct BinaryIndexedTree<T, F> {
    size: usize,
    data: Box<[T]>,
    e: T,
    f: F,
}

impl<T, F> BinaryIndexedTree<T, F>
where
    T: Copy,
    F: Fn(T, T) -> T,
{
    fn from(data: Vec<T>, e: T, f: F) -> Self {
        let size = data.len();
        let mut data = data.into_boxed_slice();
        for i in 1..size + 1 {
            let j = i + (i & i.wrapping_neg()) - 1;
            if j < size {
                data[j] = f(data[i - 1], data[j]);
            }
        }
        Self { size, data, e, f }
    }
    fn update(&mut self, mut i: usize, v: T) {
        assert!(i <= self.size);
        i += 1;
        while i <= self.size {
            self.data[i - 1] = (self.f)(v, self.data[i - 1]);
            i += i & i.wrapping_neg();
        }
    }
    fn prefix(&self, mut i: usize) -> T {
        assert!(i <= self.size);
        let mut ret = self.e;
        while i != 0 {
            ret = (self.f)(ret, self.data[i - 1]);
            i &= i - 1;
        }
        ret
    }
    fn max_right<P: Fn(T) -> bool>(&self, pred: P) -> (usize, T) {
        let mut i = 0;
        let mut acc = self.e;
        let mut len = 1 << self.size.ilog2();
        while len != 0 {
            if i + len <= self.size && pred((self.f)(acc, self.data[i + len - 1])) {
                i += len;
                acc = (self.f)(acc, self.data[i - 1]);
            }
            len >>= 1;
        }
        (i, acc)
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let mut a = sc.read_vec::<i64>(n - 1);
    let mut sum = a.iter().sum::<i64>();
    let mut bit = BinaryIndexedTree::from(a.clone(), 0, std::ops::Add::add);
    let k = sc.read::<usize>();
    let (i, small) = bit.max_right(|x| x * 2 <= sum);
    let ans1 = sum - small * 2;
    let ans2 = bit.prefix(i + 1) * 2 - sum;
    writeln!(bw, "{}", ans1.min(ans2)).ok();
    for _ in 0..k {
        let i = sc.read::<usize>() - 1;
        let x = sc.read::<i64>();
        let diff = x - std::mem::replace(&mut a[i], x);
        sum += diff;
        bit.update(i, diff);
        let (i, small) = bit.max_right(|x| x * 2 <= sum);
        let ans1 = sum - small * 2;
        let ans2 = bit.prefix(i + 1) * 2 - sum;
        writeln!(bw, "{}", ans1.min(ans2)).ok();
    }
}
