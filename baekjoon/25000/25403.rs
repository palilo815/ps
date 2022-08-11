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

struct LazySeg<T, U, F1, F2, F3> {
    size: usize,
    height: usize,
    tree: Vec<T>,
    lazy: Vec<U>,
    id: T,
    off: U,
    op: F1,
    mapping: F2,
    composition: F3,
}

impl<T, U, F1, F2, F3> std::ops::Index<usize> for LazySeg<T, U, F1, F2, F3> {
    type Output = T;
    fn index(&self, i: usize) -> &T {
        &self.tree[i | self.size]
    }
}
impl<T, U, F1, F2, F3> std::ops::IndexMut<usize> for LazySeg<T, U, F1, F2, F3> {
    fn index_mut(&mut self, i: usize) -> &mut T {
        &mut self.tree[i | self.size]
    }
}

impl<T, U, F1, F2, F3> LazySeg<T, U, F1, F2, F3>
where
    T: Clone + std::marker::Copy,
    U: Clone + std::marker::Copy + std::cmp::PartialEq,
    F1: Fn(&T, &T) -> T,
    F2: Fn(&mut T, &U),
    F3: Fn(&mut U, &U),
{
    fn new(size: usize, id: T, off: U, op: F1, mapping: F2, composition: F3) -> Self {
        let size = size.next_power_of_two();
        let height = size.trailing_zeros() as usize + 1;
        LazySeg {
            size,
            height,
            tree: vec![id; size << 1],
            lazy: vec![off; size],
            id,
            off,
            op,
            mapping,
            composition,
        }
    }
    fn build(&mut self) {
        (1..self.size).rev().for_each(|i| self._pull(i));
    }
    fn apply(&mut self, mut l: usize, mut r: usize, f: U) {
        assert!(l <= r && r <= self.size);
        if l == r {
            return;
        }
        l |= self.size;
        r += self.size;
        for i in (1..self.height).rev() {
            if (l >> i << i) != l {
                self._push(l >> i);
            }
            if (r >> i << i) != r {
                self._push((r - 1) >> i);
            }
        }
        {
            let mut l = l;
            let mut r = r;
            while l != r {
                if l & 1 == 1 {
                    self._all_apply(l, f);
                    l += 1;
                }
                if r & 1 == 1 {
                    r -= 1;
                    self._all_apply(r, f);
                }
                l >>= 1;
                r >>= 1;
            }
        }
        for i in 1..self.height {
            if (l >> i << i) != l {
                self._pull(l >> i)
            };
            if (r >> i << i) != r {
                self._pull((r - 1) >> i)
            };
        }
    }
    fn all_product(&self) -> T {
        self.tree[1]
    }
    fn _pull(&mut self, i: usize) {
        self.tree[i] = (self.op)(&self.tree[i << 1], &self.tree[i << 1 | 1]);
    }
    fn _push(&mut self, i: usize) {
        self._all_apply(i << 1, self.lazy[i]);
        self._all_apply(i << 1 | 1, self.lazy[i]);
        self.lazy[i] = self.off;
    }
    fn _all_apply(&mut self, i: usize, f: U) {
        (self.mapping)(&mut self.tree[i], &f);
        if i & self.size == 0 {
            (self.composition)(&mut self.lazy[i], &f);
        }
    }
}

fn run<W: Write>(sc: &mut Scanner, out: &mut BufWriter<W>) {
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let w = sc.read::<i32>();
    let h = sc.read::<i32>();
    let mut dots = vec![(0, 0, 0); n + m];
    for dot in dots.iter_mut().take(n) {
        dot.0 = sc.read::<i32>();
        dot.1 = sc.read::<i32>();
        dot.2 = 1;
    }
    for dot in dots.iter_mut().skip(n) {
        dot.0 = sc.read::<i32>();
        dot.1 = sc.read::<i32>();
        dot.2 = -1;
    }
    dots.sort_unstable_by(|l, r| l.1.cmp(&r.1).then(l.0.cmp(&r.0)));
    let mut xs = vec![0; (n + m) << 1];
    for (i, dot) in dots.iter().enumerate() {
        xs[i << 1] = dot.0 + 1;
        xs[i << 1 | 1] = dot.0 - w;
    }
    xs.sort_unstable();
    xs.dedup();
    let intervals = dots
        .iter()
        .map(|dot| {
            (
                xs.partition_point(|&x| x < dot.0 - w),
                xs.partition_point(|&x| x < dot.0 + 1),
            )
        })
        .collect::<Vec<_>>();
    let mut seg = LazySeg::new(
        xs.len(),
        ((0, 0), (0, 0)), // min, min_id, max, max_id
        0,
        |l, r| {
            let mut p = ((0, 0), (0, 0));
            p.0 = if l.0.0 < r.0.0 {
                l.0
            } else {
                r.0
            };
            p.1 = if l.1.0 > r.1.0 {
                l.1
            } else {
                r.1
            };
            p
        },
        |node, tag| {
            node.0 .0 += tag;
            node.1 .0 += tag
        },
        |tag, f| *tag += f,
    );
    for (i, &x) in xs.iter().enumerate() {
        seg[i].0.1 = x;
        seg[i].1.1 = x;
    }
    seg.build();
    let mut ans = (0, 0, 0);
    let mut l = 0;
    for r in 0..dots.len() {
        while dots[l].1 + h < dots[r].1 {
            seg.apply(intervals[l].0, intervals[l].1, -dots[l].2);
            if dots[l].1 != dots[l + 1].1 && dots[l].1 + 1 + h < dots[r].1 {
                let res = seg.all_product();
                let mut res = if i32::abs(res.0 .0) > i32::abs(res.1 .0) {
                    res.0
                } else {
                    res.1
                };
                res.0 = i32::abs(res.0);
                if ans.0 < res.0 {
                    ans = (res.0, res.1, dots[l].1 + 1);
                }
            }
            l += 1;
        }
        seg.apply(intervals[r].0, intervals[r].1, dots[r].2);
        if r + 1 == dots.len() || dots[r].1 != dots[r + 1].1 {
            let res = seg.all_product();
            let mut res = if i32::abs(res.0 .0) > i32::abs(res.1 .0) {
                res.0
            } else {
                res.1
            };
            res.0 = i32::abs(res.0);
            if ans.0 < res.0 {
                ans = (res.0, res.1, dots[r].1 - h);
            }
        }
    }
    while l + 1 != dots.len() {
        seg.apply(intervals[l].0, intervals[l].1, -dots[l].2);
        if dots[l].1 != dots[l + 1].1 {
            let res = seg.all_product();
            let mut res = if i32::abs(res.0 .0) > i32::abs(res.1 .0) {
                res.0
            } else {
                res.1
            };
            res.0 = i32::abs(res.0);
            if ans.0 < res.0 {
                ans = (res.0, res.1, dots[l].1 + 1);
            }
        }
        l += 1;
    }
    writeln!(out, "{}\n{} {}", ans.0, ans.1, ans.2).ok();
}
