/**
* @date     2022-01-29
* @author   palilo
* @brief    range update & range query segment tree
* @usage    `let sparse = SparseTable::new(a, |&lhs, &rhs| lhs.min(rhs));`
*               -> range minimum query for `a`
* @test     https://judge.yosupo.jp/submission/76204
*/
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
        (self.op)(&lson, &rson)
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
