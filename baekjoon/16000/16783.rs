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

struct SegmentTree<T, F> {
    size: usize,
    data: Box<[T]>,
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
        Self {
            size,
            data: vec![e; size << 1].into(),
            f,
        }
    }
    fn build(&mut self) {
        for i in (1..self.size).rev() {
            self.data[i] = (self.f)(self.data[i << 1], self.data[i << 1 | 1]);
        }
    }
    fn set(&mut self, mut i: usize, x: T) {
        assert!(i < self.size);
        i += self.size;
        self.data[i] = x;
        while i != 1 {
            i >>= 1;
            self.data[i] = (self.f)(self.data[i << 1], self.data[i << 1 | 1]);
        }
    }
    fn all_prod(&mut self) -> T {
        self.data[1]
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let mut a = (0..n).map(|_| (sc.read::<i64>(), sc.read::<i64>(), sc.read::<i64>())).collect::<Vec<_>>();
    a.sort_unstable_by(|l, r| l.0.cmp(&r.0).then(l.1.cmp(&r.1)));
    let mut slopes = Vec::with_capacity(n * (n - 1) / 2);
    for j in 1..n {
        for i in 0..j {
            if a[i].0 == a[j].0 {
                break;
            }
            slopes.push((a[j].1 - a[i].1, a[j].0 - a[i].0, i, j));
        }
    }
    slopes.sort_unstable_by(|l, r| (l.0 * r.1).cmp(&(r.0 * l.1)).then((l.2, l.3).cmp(&(r.2, r.3))));
    const INF: i64 = 0x3f3f3f3f3f3f3f3f;
    let mut seg = SegmentTree::new(n + 1, (INF, !INF, 0), |l, r| {
        (l.0.min(r.0), l.1.max(r.1), (r.1 - l.0).max(l.2.max(r.2)))
    });
    seg[0] = (0, 0, 0);
    for i in 0..n {
        seg[i + 1] = (seg[i].0 + a[i].2, seg[i].0 + a[i].2, 0);
    }
    seg.build();
    let mut ans = seg.all_prod().2;
    let mut idx = (0..n).collect::<Vec<_>>();
    let mut i = 0;
    while i != slopes.len() {
        let s = (slopes[i].0, slopes[i].1);
        while i != slopes.len() && slopes[i].0 * s.1 == s.0 * slopes[i].1 {
            let k = idx[slopes[i].2];
            let dl = seg[k + 1].0 - seg[k].0;
            let dr = if k == n - 1 { 0 } else { seg[k + 2].0 } - seg[k + 1].0;
            seg.set(k + 1, (seg[k + 1].0 + dr - dl, seg[k + 1].0 + dr - dl, 0));
            idx.swap(slopes[i].2, slopes[i].3);
            i += 1;
        }
        ans = ans.max(seg.all_prod().2);
    }
    writeln!(bw, "{ans}").ok();
}
