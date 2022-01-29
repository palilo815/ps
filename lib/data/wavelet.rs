/**
* @date     2020-01-30
* @author   palilo
* @test     `kth_smallest`  https://judge.yosupo.jp/submission/76253
*                           https://www.acmicpc.net/source/38330373
*/
mod wavelet {
    type T = i32;

    #[derive(Clone)]
    struct BitVec {
        bits: Vec<u64>,
        pref: Vec<u32>,
    }

    impl BitVec {
        fn new(size: usize) -> Self {
            let size = (size >> 6) + 1;
            Self {
                bits: vec![0; size],
                pref: vec![0; size + 1],
            }
        }
        fn build(&mut self) {
            for (i, bits) in self.bits.iter().enumerate() {
                self.pref[i + 1] = self.pref[i] + bits.count_ones();
            }
        }
        fn set(&mut self, i: usize) {
            self.bits[i >> 6] |= 1 << (i & 63);
        }
        fn count_prefix(&self, r: usize, value: bool) -> usize {
            if value {
                self.rank(r)
            } else {
                r - self.rank(r)
            }
        }
        fn count_range(&self, l: usize, r: usize, value: bool) -> usize {
            if value {
                self.rank(r) - self.rank(l)
            } else {
                (r - l) - (self.rank(r) - self.rank(l))
            }
        }
        fn rank(&self, r: usize) -> usize {
            (self.pref[r >> 6] + (self.bits[r >> 6] & (1 << (r & 63)) - 1).count_ones()) as usize
        }
    }

    pub struct Matrix {
        height: usize,
        matrix: Vec<BitVec>,
        fence: Vec<usize>,
    }

    #[allow(dead_code)]
    impl Matrix {
        pub fn new(mut data: Vec<T>) -> Self {
            let size = data.len();
            let height = 32 - data.iter().max().unwrap().leading_zeros() as usize;
            let mut matrix = vec![BitVec::new(size); height];
            let mut fence = vec![0; height];
            let mut buf = vec![0; size];
            for h in (0..height).rev() {
                let (mut lo, mut hi) = (0, size);
                for (i, x) in data.iter().enumerate() {
                    if x >> h & 1 == 1 {
                        matrix[h].set(i);
                        hi -= 1;
                        buf[hi] = data[i];
                    } else {
                        buf[lo] = data[i];
                        lo += 1;
                    }
                }
                matrix[h].build();
                fence[h] = lo;
                buf[lo..].reverse();
                std::mem::swap(&mut data, &mut buf);
            }
            Self {
                height,
                matrix,
                fence,
            }
        }
        pub fn rank(&self, mut l: usize, mut r: usize, x: T) -> usize {
            for h in (0..self.height).rev() {
                let bit = x >> h & 1 == 1;
                l = self.matrix[h].count_prefix(l, bit) + if bit { self.fence[h] } else { 0 };
                r = self.matrix[h].count_prefix(r, bit) + if bit { self.fence[h] } else { 0 };
            }
            r - l
        }
        pub fn prefix_freq(&self, mut l: usize, mut r: usize, upper: T) -> usize {
            let mut ret = 0;
            for h in (0..self.height).rev() {
                let bit = upper >> h & 1 == 1;
                if bit {
                    ret += self.matrix[h].count_range(l, r, false);
                }
                l = self.matrix[h].count_prefix(l, bit) + if bit { self.fence[h] } else { 0 };
                r = self.matrix[h].count_prefix(r, bit) + if bit { self.fence[h] } else { 0 };
            }
            ret
        }
        pub fn range_freq(&self, l: usize, r: usize, lower: T, upper: T) -> usize {
            self.prefix_freq(l, r, upper) - self.prefix_freq(l, r, lower)
        }
        pub fn kth_smallest(&self, mut l: usize, mut r: usize, mut k: usize) -> T {
            let mut ret = 0;
            for h in (0..self.height).rev() {
                let zeros = self.matrix[h].count_range(l, r, false);
                let bit = zeros <= k;
                if bit {
                    ret |= 1 << h;
                    k -= zeros;
                }
                l = self.matrix[h].count_prefix(l, bit) + if bit { self.fence[h] } else { 0 };
                r = self.matrix[h].count_prefix(r, bit) + if bit { self.fence[h] } else { 0 };
            }
            ret
        }
        pub fn kth_largest(&self, l: usize, r: usize, k: usize) -> T {
            self.kth_smallest(l, r, r - l - k - 1)
        }
    }
}
