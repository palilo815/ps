pub trait Monoid: std::clone::Clone + std::marker::Copy {
    fn id() -> Self;
    fn op(lhs: &Self, rhs: &Self) -> Self;
    fn rev_op(lhs: &Self, rhs: &Self) -> Self;
}

#[allow(dead_code)]
mod binary_indexed_tree {
    use crate::Monoid;
    pub struct BinaryIndexedTree<T: Monoid> {
        n: usize,
        tree: Vec<T>,
    }
    impl<T: Monoid> BinaryIndexedTree<T> {
        pub fn new(n: usize) -> Self {
            Self {
                n,
                tree: vec![T::id(); n + 1],
            }
        }
        pub fn build_with(data: Vec<T>) -> Self {
            let n = data.len();
            let mut a = vec![T::id(); n + 1];
            a[1..].copy_from_slice(&data);
            for i in 1..=n {
                let j = i + (i & i.wrapping_neg());
                if j <= n {
                    a[j] = T::op(&a[i], &a[j]);
                }
            }
            Self { n, tree: a }
        }
        pub fn get(&self, i: usize) -> T {
            assert!(i < self.n);
            if i & 1 == 0 {
                self.product(i, i + 1)
            } else {
                self.tree[i + 1]
            }
        }
        pub fn update(&mut self, mut i: usize, x: T) {
            assert!(i <= self.n);
            i += 1;
            while i <= self.n {
                self.tree[i] = T::op(&self.tree[i], &x);
                i += i & i.wrapping_neg();
            }
        }
        pub fn prefix(&self, mut i: usize) -> T {
            assert!(i <= self.n);
            let mut ret = T::id();
            while i != 0 {
                ret = T::op(&ret, &self.tree[i]);
                i &= i - 1;
            }
            ret
        }
        pub fn product(&self, l: usize, r: usize) -> T {
            assert!(l <= r);
            T::rev_op(&self.prefix(l), &self.prefix(r))
        }
        pub fn clear(&mut self) {
            self.tree.fill(T::id());
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
    fn rev_op(lhs: &Self, rhs: &Self) -> Self {
        // TODO
    }
}
