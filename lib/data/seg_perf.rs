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

#[allow(dead_code)]
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
    fn from(leaves: Vec<T>, id: T, op: F) -> Self {
        let size = leaves.len().next_power_of_two();
        let mut tree = vec![id; size << 1];
        tree[size..(size + leaves.len())].copy_from_slice(&leaves);
        for i in (1..size).rev() {
            tree[i] = op(&tree[i << 1], &tree[i << 1 | 1]);
        }
        Self { size, tree, id, op }
    }
    fn build(&mut self) {
        for i in (1..self.size).rev() {
            self.tree[i] = (self.op)(&self.tree[i << 1], &self.tree[i << 1 | 1]);
        }
    }
    fn clear(&mut self) {
        self.tree[1..].fill(self.id);
    }
    fn set(&mut self, mut i: usize, x: T) {
        assert!(i < self.size);
        i |= self.size;
        self.tree[i] = x;
        while i != 1 {
            i >>= 1;
            self.tree[i] = (self.op)(&self.tree[i << 1], &self.tree[i << 1 | 1]);
        }
    }
    fn update(&mut self, mut i: usize, x: T) {
        assert!(i < self.size);
        i |= self.size;
        self.tree[i] = (self.op)(&self.tree[i], &x);
        while i != 1 {
            i >>= 1;
            self.tree[i] = (self.op)(&self.tree[i << 1], &self.tree[i << 1 | 1]);
        }
    }
    fn product(&self, mut l: usize, mut r: usize) -> T {
        assert!(l <= r && r <= self.size);
        let mut res_l = self.id;
        let mut res_r = self.id;
        l += self.size;
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
    fn all_product(&self) -> T {
        self.tree[1]
    }
}
