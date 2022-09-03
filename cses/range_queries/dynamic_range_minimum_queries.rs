use std::io::*;

struct Scanner<'a> {
    it: std::str::SplitWhitespace<'a>,
}

impl<'a> Scanner<'a> {
    fn new(s: &'a str) -> Scanner<'a> {
        Scanner {
            it: s.split_whitespace(),
        }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
}

fn main() {
    let mut s = String::new();
    stdin().read_to_string(&mut s).unwrap();
    let mut sc = Scanner::new(&s);
    let out = stdout();
    let mut out = BufWriter::new(out.lock());
    run(&mut sc, &mut out);
}

struct SegmentTree<T, F> {
    size: usize,
    tree: Vec<T>,
    id: T,
    op: F,
}

impl<T, F> std::ops::Index<usize> for SegmentTree<T, F> {
    type Output = T;
    fn index(&self, i: usize) -> &T {
        &self.tree[i + self.size]
    }
}
impl<T, F> std::ops::IndexMut<usize> for SegmentTree<T, F> {
    fn index_mut(&mut self, i: usize) -> &mut T {
        &mut self.tree[i + self.size]
    }
}

impl<T, F> SegmentTree<T, F>
where
    T: Clone + std::marker::Copy,
    F: Fn(&T, &T) -> T,
{
    fn new(size: usize, id: T, op: F) -> Self {
        SegmentTree {
            size,
            tree: vec![id; size << 1],
            id,
            op,
        }
    }
    fn build(&mut self) {
        for i in (1..self.size).rev() {
            self.tree[i] = (self.op)(&self.tree[i << 1], &self.tree[i << 1 | 1]);
        }
    }
    fn set(&mut self, mut i: usize, x: T) {
        assert!(i < self.size);
        i += self.size;
        self.tree[i] = x;
        while i != 1 {
            i >>= 1;
            self.tree[i] = (self.op)(&self.tree[i << 1], &self.tree[i << 1 | 1]);
        }
    }
    fn product(&self, mut l: usize, mut r: usize) -> T {
        assert!(l <= r && r <= self.size);
        let mut ret = self.id;
        l += self.size;
        r += self.size;
        while l != r {
            if l & 1 == 1 {
                ret = (self.op)(&ret, &self.tree[l]);
                l += 1;
            }
            if r & 1 == 1 {
                r -= 1;
                ret = (self.op)(&self.tree[r], &ret);
            }
            l >>= 1;
            r >>= 1;
        }
        ret
    }
}

fn run<W: Write>(sc: &mut Scanner, out: &mut BufWriter<W>) {
    let n = sc.read::<usize>();
    let q = sc.read::<usize>();
    let mut seg = SegmentTree::new(n, u32::MAX, |&lhs, &rhs| lhs.min(rhs));
    for i in 0..n {
        seg[i] = sc.read::<u32>();
    }
    seg.build();
    for _ in 0..q {
        match sc.read::<usize>() {
            1 => seg.set(sc.read::<usize>() - 1, sc.read::<u32>()),
            _ => writeln!(
                out,
                "{}",
                seg.product(sc.read::<usize>() - 1, sc.read::<usize>())
            )
            .unwrap(),
        }
    }
}
