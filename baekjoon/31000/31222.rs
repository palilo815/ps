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

struct SegmentTree<T, F> {
    size: usize,
    data: Box<[T]>,
    e: T,
    f: F,
}

impl<T, F> std::ops::Index<usize> for SegmentTree<T, F> {
    type Output = T;
    fn index(&self, i: usize) -> &T {
        &self.data[i + self.size]
    }
}
impl<T, F> std::ops::IndexMut<usize> for SegmentTree<T, F> {
    fn index_mut(&mut self, i: usize) -> &mut T {
        &mut self.data[i + self.size]
    }
}

impl<T, F> SegmentTree<T, F>
where
    T: Clone + Copy,
    F: Fn(T, T) -> T,
{
    fn new(size: usize, e: T, f: F) -> Self {
        let size = size.next_power_of_two();
        let data = vec![e; size << 1].into_boxed_slice();
        Self { size, data, e, f }
    }
    fn build(&mut self) {
        (1..self.size).rev().for_each(|i| self._pull(i));
    }
    fn set(&mut self, mut i: usize, x: T) {
        assert!(i < self.size);
        i += self.size;
        self.data[i] = x;
        while i != 1 {
            i >>= 1;
            self._pull(i);
        }
    }
    fn prod(&self, range: std::ops::Range<usize>) -> T {
        assert!(range.start <= range.end && range.end <= self.size);
        let mut l = self.size + range.start;
        let mut r = self.size + range.end;
        let mut prod_l = self.e;
        let mut prod_r = self.e;
        while l != r {
            if l & 1 == 1 {
                prod_l = (self.f)(prod_l, self.data[l]);
                l += 1;
            }
            if r & 1 == 1 {
                r -= 1;
                prod_r = (self.f)(self.data[r], prod_r);
            }
            l >>= 1;
            r >>= 1;
        }
        (self.f)(prod_l, prod_r)
    }
    #[inline]
    fn _pull(&mut self, i: usize) {
        self.data[i] = (self.f)(self.data[i << 1], self.data[i << 1 | 1]);
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let q = sc.read::<usize>();
    let mut seg = SegmentTree::new(n, (-1, -1, 0), |l, r| (l.0, r.1, l.2 + r.2 - (l.1 == r.0) as i32));
    for i in 0..n {
        let x = sc.read::<i32>();
        seg[i] = (x, x, 1);
    }
    seg.build();
    for _ in 0..q {
        match sc.read::<char>() {
            '1' => {
                let i = sc.read::<usize>() - 1;
                let x = sc.read::<i32>();
                seg.set(i, (x, x, 1));
            }
            _ => {
                let l = sc.read::<usize>() - 1;
                let r = sc.read::<usize>();
                writeln!(bw, "{}", seg.prod(l..r).2).ok();
            }
        }
    }
}
