pub struct BinaryIndexedTree<T> {
    size: usize,
    tree: Vec<T>,
    id: T,
}

#[allow(dead_code)]
impl<T> BinaryIndexedTree<T>
where
    T: std::clone::Clone
        + std::cmp::PartialOrd
        + std::marker::Copy
        + std::ops::AddAssign
        + std::ops::SubAssign
        + std::ops::Sub<Output = T>,
{
    pub fn new(size: usize, id: T) -> Self {
        BinaryIndexedTree {
            size,
            tree: vec![id; size + 1],
            id,
        }
    }
    pub fn build(&mut self) {
        for i in 1..self.size {
            let val = self.tree[i];
            let idx = i + (i & i.wrapping_neg());
            if idx <= self.size {
                self.tree[idx] += val;
            }
        }
    }
    pub fn clear(&mut self) {
        self.tree[1..].fill(self.id);
    }
    pub fn get(&self, i: usize) -> T {
        assert!(i < self.size);
        if i & 1 == 0 {
            self.product(i, i + 1)
        } else {
            self.tree[i + 1]
        }
    }
    pub fn fake_update(&mut self, i: usize, x: T) {
        self.tree[i + 1] += x;
    }
    pub fn update(&mut self, mut i: usize, x: T) {
        assert!(i <= self.size);
        i += 1;
        while i <= self.size {
            self.tree[i] += x;
            i += i & i.wrapping_neg();
        }
    }
    pub fn prefix(&self, mut i: usize) -> T {
        assert!(i <= self.size);
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
    pub fn lower_bound(&self, mut k: T) -> usize {
        let mut i = 0;
        let mut pw = 1 << 20;
        while pw != 0 {
            if (i | pw) <= self.size && self.tree[i | pw] < k {
                i |= pw;
                k -= self.tree[i];
            }
            pw >>= 1;
        }
        i
    }
    pub fn upper_bound(&self, mut k: T) -> usize {
        let mut i = 0;
        let mut pw = 1 << 20;
        while pw != 0 {
            if (i | pw) <= self.size && self.tree[i | pw] <= k {
                i |= pw;
                k -= self.tree[i];
            }
            pw >>= 1;
        }
        i
    }
}
