pub struct SegmentTree<T, F> {
    size: usize,
    tree: Vec<T>,
    id: T,
    op: F,
}

impl<T, F> std::ops::Index<usize> for SegmentTree<T, F> {
    type Output = T;
    fn index(&self, i: usize) -> &T {
        assert!(i < self.size);
        &self.tree[i + self.size]
    }
}
impl<T, F> std::ops::IndexMut<usize> for SegmentTree<T, F> {
    fn index_mut(&mut self, i: usize) -> &mut T {
        assert!(i < self.size);
        &mut self.tree[i + self.size]
    }
}

#[allow(dead_code)]
impl<T, F> SegmentTree<T, F>
where
    T: Clone + std::marker::Copy,
    F: Fn(&T, &T) -> T,
{
    pub fn new(size: usize, id: T, op: F) -> Self {
        SegmentTree {
            size,
            tree: vec![id; size << 1],
            id,
            op,
        }
    }
    pub fn from(leaves: Vec<T>, id: T, op: F) -> Self {
        let size = leaves.len();
        let mut tree = leaves;
        tree.extend_from_within(..);
        for i in (1..size).rev() {
            tree[i] = op(&tree[i << 1], &tree[i << 1 | 1]);
        }
        tree[0] = id;
        Self { size, tree, id, op }
    }
    pub fn build(&mut self) {
        for i in (1..self.size).rev() {
            self.tree[i] = (self.op)(&self.tree[i << 1], &self.tree[i << 1 | 1]);
        }
    }
    pub fn set(&mut self, mut i: usize, x: T) {
        assert!(i < self.size);
        i += self.size;
        self.tree[i] = x;
        while i != 1 {
            i >>= 1;
            self.tree[i] = (self.op)(&self.tree[i << 1], &self.tree[i << 1 | 1]);
        }
    }
    pub fn update(&mut self, mut i: usize, x: T) {
        assert!(i < self.size);
        i += self.size;
        self.tree[i] = (self.op)(&self.tree[i], &x);
        while i != 1 {
            i >>= 1;
            self.tree[i] = (self.op)(&self.tree[i << 1], &self.tree[i << 1 | 1]);
        }
    }
    pub fn product(&self, mut l: usize, mut r: usize) -> T {
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
    pub fn all_prod(&self) -> T {
        self.tree[1]
    }
}
