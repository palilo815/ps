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
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
    }
}

pub struct BinaryIndexedTree<T> {
    tree: Box<[T]>,
    id: T,
}

impl<T> BinaryIndexedTree<T>
where
    T: std::clone::Clone
        + std::cmp::PartialOrd
        + std::marker::Copy
        + std::ops::AddAssign
        + std::ops::Sub<Output = T>,
{
    pub fn new(size: usize, id: T) -> Self {
        Self {
            tree: vec![id; size + 1].into_boxed_slice(),
            id,
        }
    }
    pub fn clear(&mut self) {
        self.tree[1..].fill(self.id);
    }
    pub fn update(&mut self, mut i: usize, x: T) {
        assert!(i < self.tree.len());
        i += 1;
        while i < self.tree.len() {
            self.tree[i] += x;
            i += i & i.wrapping_neg();
        }
    }
    pub fn prefix(&self, mut i: usize) -> T {
        assert!(i < self.tree.len());
        let mut ret = self.id;
        while i != 0 {
            ret += self.tree[i];
            i &= i - 1;
        }
        ret
    }
    pub fn product(&self, l: usize, r: usize) -> T {
        assert!(l <= r);
        self.prefix(r) - self.prefix(l)
    }
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let q = sc.read::<usize>();
    let p = sc.read_vec::<usize>(n);
    let queries = (0..q)
        .map(|_| (sc.read::<usize>() - 1, sc.read::<usize>()))
        .collect::<Vec<_>>();
    let mut indices = (0..n).collect::<Vec<_>>();
    indices.sort_unstable_by(|&l, &r| p[r].cmp(&p[l]));
    let mut intervals = vec![(1, n); q];
    let mut head = vec![usize::MAX; n];
    let mut next = vec![usize::MAX; n];
    let mut bit = BinaryIndexedTree::new(n, 0);
    loop {
        let mut update = false;
        for (i, &(l, r)) in intervals.iter().enumerate() {
            if l != r {
                let m = r - (r - l) / 2;
                next[i] = head[m];
                head[m] = i;
                update = true;
            }
        }
        if !update {
            break;
        }
        bit.clear();
        let mut i = 0;
        for (h, node) in head.iter_mut().enumerate().rev() {
            if *node == usize::MAX {
                continue;
            }
            while i != n && p[indices[i]] >= h {
                bit.update(indices[i], 1);
                i += 1;
            }
            let mut node = std::mem::replace(node, usize::MAX);
            while node != usize::MAX {
                if bit.product(queries[node].0, queries[node].1) < h {
                    intervals[node].1 = h - 1;
                } else {
                    intervals[node].0 = h;
                }
                node = next[node];
            }
        }
    }
    for (lo, _) in intervals.into_iter() {
        writeln!(out, "{lo}").ok();
    }
}
