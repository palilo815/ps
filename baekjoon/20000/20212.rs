use std::io::Write;

#[allow(dead_code)]
mod scanner {
    use std::str::FromStr;
    pub struct Scanner<'a> {
        it: std::str::SplitWhitespace<'a>,
    }
    impl<'a> Scanner<'a> {
        pub fn new(s: &'a str) -> Scanner<'a> {
            Scanner {
                it: s.split_whitespace(),
            }
        }
        pub fn next<T: FromStr>(&mut self) -> T {
            self.it.next().unwrap().parse::<T>().ok().unwrap()
        }
        pub fn next_bytes(&mut self) -> Vec<u8> {
            self.it.next().unwrap().bytes().collect()
        }
        pub fn next_chars(&mut self) -> Vec<char> {
            self.it.next().unwrap().chars().collect()
        }
        pub fn next_vec<T: FromStr>(&mut self, len: usize) -> Vec<T> {
            (0..len).map(|_| self.next()).collect()
        }
    }
}

fn main() {
    use std::io::Read;
    let mut s = String::new();
    std::io::stdin().read_to_string(&mut s).unwrap();
    let mut sc = scanner::Scanner::new(&s);
    let out = std::io::stdout();
    let mut out = std::io::BufWriter::new(out.lock());
    run(&mut sc, &mut out);
}

struct LazySeg<T, U, F1, F2, F3> {
    size: usize,
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

#[allow(dead_code)]
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
        LazySeg {
            size,
            tree: vec![id; size << 1],
            lazy: vec![off; size],
            id,
            off,
            op,
            mapping,
            composition,
        }
    }
    fn from(leaves: Vec<T>, id: T, off: U, op: F1, mapping: F2, composition: F3) -> Self {
        let size = leaves.len().next_power_of_two();
        let mut tree = vec![id; size << 1];
        tree[size..(size + leaves.len())].copy_from_slice(&leaves);
        for i in (1..size).rev() {
            tree[i] = op(&tree[i << 1], &tree[i << 1 | 1]);
        }
        let lazy = vec![off; size];
        Self {
            size,
            tree,
            lazy,
            id,
            off,
            op,
            mapping,
            composition,
        }
    }
    fn build(&mut self) {
        for i in (1..self.size).rev() {
            self.tree[i] = (self.op)(&self.tree[i << 1], &self.tree[i << 1 | 1]);
        }
    }
    fn clear(&mut self) {
        self.tree[1..].fill(self.id);
        self.lazy[1..].fill(self.off);
    }
    fn apply(&mut self, l: usize, r: usize, f: U) {
        assert!(l <= r && r <= self.size);
        self._apply(l, r, f, 0, self.size, 1);
    }
    fn product(&mut self, l: usize, r: usize) -> T {
        assert!(l <= r && r <= self.size);
        self._product(l, r, 0, self.size, 1)
    }
    fn all_product(&self) -> T {
        self.tree[1]
    }
    fn _apply(&mut self, ql: usize, qr: usize, f: U, l: usize, r: usize, i: usize) {
        if qr <= l || r <= ql {
            return;
        }
        if ql <= l && r <= qr {
            self._all_apply(i, f);
            return;
        }
        if self.lazy[i] != self.off {
            self._push(i);
        }
        let m = (l + r) >> 1;
        self._apply(ql, qr, f, l, m, i << 1);
        self._apply(ql, qr, f, m, r, i << 1 | 1);
        self._pull(i);
    }
    fn _product(&mut self, ql: usize, qr: usize, l: usize, r: usize, i: usize) -> T {
        if qr <= l || r <= ql {
            return self.id;
        }
        if ql <= l && r <= qr {
            return self.tree[i];
        };
        if self.lazy[i] != self.off {
            self._push(i);
        }
        let m = (l + r) >> 1;
        let lson = &self._product(ql, qr, l, m, i << 1);
        let rson = &self._product(ql, qr, m, r, i << 1 | 1);
        (self.op)(lson, rson)
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

fn run<W: Write>(sc: &mut scanner::Scanner, out: &mut std::io::BufWriter<W>) {
    let n = sc.next::<usize>();
    let mut q1 = vec![];
    let mut q2 = vec![];
    for _ in 0..n {
        let q = sc.next::<u32>();
        let l = sc.next::<u32>() - 1;
        let r = sc.next::<u32>();
        let k = sc.next::<i32>();
        if q == 1 {
            q1.push((l, r, k));
        } else {
            q2.push((l, r, k - 1, q2.len() as u32));
        }
    }
    let mut indices = q1
        .iter()
        .flat_map(|x| [x.0, x.1])
        .chain(q2.iter().flat_map(|x| [x.0, x.1]))
        .collect::<Vec<_>>();
    indices.sort_unstable();
    indices.dedup();
    q1.iter_mut().for_each(|(l, r, _)| {
        *l = indices.binary_search(l).unwrap() as u32;
        *r = indices.binary_search(r).unwrap() as u32;
    });
    q2.iter_mut().for_each(|(l, r, _, _)| {
        *l = indices.binary_search(l).unwrap() as u32;
        *r = indices.binary_search(r).unwrap() as u32;
    });
    let mut seg = LazySeg::new(
        indices.len() - 1,
        (0_i64, 0_i64), // (sum, length)
        0_i64,
        |lson, rson| (lson.0 + rson.0, lson.1 + rson.1),
        |node, tag| node.0 += node.1 * tag,
        |tag, f| *tag += f,
    );
    for (i, x) in indices.windows(2).enumerate() {
        seg[i].1 = (x[1] - x[0]) as i64;
    }
    seg.build();
    let mut ans = vec![0; q2.len()];
    q2.sort_unstable_by_key(|x| x.2);
    q2.push((0, 0, -1, 0)); // sentinel
    let mut j = 0;
    for (i, (l, r, k)) in q1.into_iter().enumerate() {
        seg.apply(l as usize, r as usize, k as i64);
        while q2[j].2 == i as i32 {
            ans[q2[j].3 as usize] = seg.product(q2[j].0 as usize, q2[j].1 as usize).0;
            j += 1;
        }
    }
    for x in ans {
        writeln!(out, "{}", x).ok();
    }
}
