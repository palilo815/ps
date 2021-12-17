pub trait Monoid: std::clone::Clone + std::marker::Copy {
    fn id() -> Self;
    fn op(lhs: &Self, rhs: &Self) -> Self;
}

mod segment_tree {
    use crate::Monoid;

    pub struct SegmentTree<T: Monoid> {
        n: usize,
        tree: Vec<T>,
    }

    #[allow(dead_code)]
    impl<T: Monoid> SegmentTree<T> {
        pub fn new(n: usize) -> Self {
            Self {
                n,
                tree: vec![T::id(); n << 1],
            }
        }
        pub fn build_with(data: Vec<T>) -> Self {
            let n = data.len();
            let mut a = vec![T::id(); n << 1];
            a[n..].copy_from_slice(&data);
            for i in (1..n).rev() {
                a[i] = T::op(&a[i << 1], &a[i << 1 | 1]);
            }
            Self { n, tree: a }
        }
        pub fn get(&self, i: usize) -> T {
            self.tree[i + self.n]
        }
        pub fn set(&mut self, mut i: usize, x: T) {
            i += self.n;
            self.tree[i] = x;
            while i != 1 {
                i >>= 1;
                self.tree[i] = T::op(&self.tree[i << 1], &self.tree[i << 1 | 1]);
            }
        }
        pub fn update(&mut self, mut i: usize, x: T) {
            i += self.n;
            self.tree[i] = T::op(&self.tree[i], &x);
            while i != 1 {
                i >>= 1;
                self.tree[i] = T::op(&self.tree[i << 1], &self.tree[i << 1 | 1]);
            }
        }
        pub fn product(&self, mut l: usize, mut r: usize) -> T {
            let mut ret = T::id();
            l += self.n;
            r += self.n;
            while l != r {
                if l & 1 == 1 {
                    ret = T::op(&ret, &self.tree[l]);
                    l += 1;
                }
                if r & 1 == 1 {
                    r -= 1;
                    ret = T::op(&self.tree[r], &ret);
                }
                l >>= 1;
                r >>= 1;
            }
            ret
        }
    }
}

// TODO
impl Monoid for TODO {
    fn id() -> Self {
        // TODO
    }
    fn op(lhs: &Self, rhs: &Self) -> Self {
        // TODO
    }
}
