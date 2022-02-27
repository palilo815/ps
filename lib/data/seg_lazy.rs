/**
* @date     2022-02-27
* @source   atcoder library
* @test     used a lot
* ----------
* @author   yosupo
* @brief    segment tree with lazy propagation
* @time     `O(\log n)` for `apply` and `product`
* @detail   .
* @usage    // range add and range sum queries
            let mut seg = LazySeg::new(
                n,
                (0, 0),
                0,
                |lhs, rhs| (lhs.0 + rhs.0, lhs.1 + rhs.1),
                |node, tag| node.0 += node.1 * tag,
                |tag, f| *tag += f,
            );
* ----------
* @todo     binary search on tree
* @warning  .
*/
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
    fn clear(&mut self) {
        self.tree[1..].fill(self.id);
        self.lazy[1..].fill(self.off);
    }
    fn apply(&mut self, mut l: usize, mut r: usize, f: U) {
        assert!(l <= r && r <= self.size);
        if l == r {
            return;
        }
        l |= self.size;
        r |= self.size;
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
    fn product(&mut self, mut l: usize, mut r: usize) -> T {
        assert!(l <= r && r <= self.size);
        if l == r {
            return self.id;
        }
        l |= self.size;
        r |= self.size;
        for i in (1..self.height).rev() {
            if (l >> i << i) != l {
                self._push(l >> i);
            }
            if (r >> i << i) != r {
                self._push((r - 1) >> i);
            }
        }
        let mut res_l = self.id;
        let mut res_r = self.id;
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
