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
    F: Fn(T, T) -> T,
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
            self.tree[i] = (self.op)(self.tree[i << 1], self.tree[i << 1 | 1]);
        }
    }
    fn product(&self, mut l: usize, mut r: usize) -> T {
        assert!(l <= r && r <= self.size);
        let mut ret = self.id;
        l += self.size;
        r += self.size;
        while l != r {
            if l & 1 == 1 {
                ret = (self.op)(ret, self.tree[l]);
                l += 1;
            }
            if r & 1 == 1 {
                r -= 1;
                ret = (self.op)(self.tree[r], ret);
            }
            l >>= 1;
            r >>= 1;
        }
        ret
    }
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let mut meat = (0..n)
        .map(|_| (sc.read::<usize>(), sc.read::<usize>(), sc.read::<u64>()))
        .collect::<Vec<_>>();
    let mut skewer = (0..m).map(|_| (sc.read::<usize>(), sc.read::<usize>())).collect::<Vec<_>>();
    let k = {
        let mut coordi = vec![0; 2 * (n + m)];
        for i in 0..n {
            coordi[2 * i] = meat[i].0;
            coordi[2 * i + 1] = meat[i].1;
        }
        for i in 0..m {
            coordi[2 * (n + i)] = skewer[i].0;
            coordi[2 * (n + i) + 1] = skewer[i].1;
        }
        coordi.sort_unstable();
        coordi.dedup();
        for x in meat.iter_mut() {
            x.0 = coordi.partition_point(|&y| y < x.0);
            x.1 = coordi.partition_point(|&y| y < x.1);
        }
        for x in skewer.iter_mut() {
            x.0 = coordi.partition_point(|&y| y < x.0);
            x.1 = coordi.partition_point(|&y| y < x.1);
        }
        coordi.len()
    };
    let mut seg = SegmentTree::new(k, usize::MAX, std::cmp::min);
    for (i, &(s, e)) in skewer.iter().enumerate().rev() {
        seg[s] = i;
        seg[e] = i;
    }
    seg.build();
    let mut ans = vec![0; m];
    for (s, e, t) in meat.into_iter() {
        let i = seg.product(s, e);
        if i != usize::MAX && s <= skewer[i].0 && skewer[i].1 < e {
            ans[i] += t;
        }
    }
    for x in ans.into_iter() {
        writeln!(out, "{x}").ok();
    }
}
