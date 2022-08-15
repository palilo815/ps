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
    fn read_bytes(&mut self) -> Vec<u8> {
        self.it.next().unwrap().bytes().collect()
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

struct PerfectSeg<T, F> {
    size: usize,
    tree: Vec<T>,
    id: T,
    op: F,
}

impl<T, F> std::ops::Index<usize> for PerfectSeg<T, F> {
    type Output = T;
    fn index(&self, i: usize) -> &T {
        &self.tree[i | self.size]
    }
}
impl<T, F> std::ops::IndexMut<usize> for PerfectSeg<T, F> {
    fn index_mut(&mut self, i: usize) -> &mut T {
        &mut self.tree[i | self.size]
    }
}

impl<T, F> PerfectSeg<T, F>
where
    T: Clone + std::marker::Copy,
    F: Fn(&T, &T) -> T,
{
    fn new(size: usize, id: T, op: F) -> Self {
        let size = size.next_power_of_two();
        PerfectSeg {
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
    fn product(&self, mut l: usize, mut r: usize) -> T {
        assert!(l <= r && r <= self.size);
        let mut res_l = self.id;
        let mut res_r = self.id;
        l |= self.size;
        r += self.size;
        while l != r {
            if l & 1 == 1 {
                res_l = (self.op)(&res_l, &self.tree[l]);
                l += 1;
            }
            if r & 1 == 1 {
                r -= 1;
                res_r = (self.op)(&self.tree[r], &res_r);
            }
            l >>= 1;
            r >>= 1;
        }
        (self.op)(&res_l, &res_r)
    }
}

fn run<W: Write>(sc: &mut Scanner, out: &mut BufWriter<W>) {
    let n = sc.read::<usize>();
    let s = sc.read_bytes();
    let mut seg = PerfectSeg::new(n, (0, 0, 0, 0), |lhs, rhs| {
        (
            lhs.0.max(lhs.2 + rhs.0),
            rhs.1.max(rhs.2 + lhs.1),
            lhs.2 + rhs.2,
            (lhs.0 + rhs.1).max(std::cmp::max(lhs.3 + rhs.2, rhs.3 + lhs.2)),
        )
    });
    for (i, x) in s.into_iter().enumerate() {
        seg[i] = if x == b'C' {
            (0, 0, -1, 0)
        } else {
            (1, 1, 1, 1)
        };
    }
    seg.build();
    let q = sc.read::<usize>();
    for _ in 0..q {
        let l = sc.read::<usize>() - 1;
        let r = sc.read::<usize>();
        writeln!(out, "{}", seg.product(l, r).3).ok();
    }
}
