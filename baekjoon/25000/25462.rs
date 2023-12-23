use std::io::*;

struct Scanner<'a> {
    it: std::str::SplitWhitespace<'a>,
}

impl<'a> Scanner<'a> {
    fn new(s: &str) -> Scanner {
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

struct FenwickTree<T> {
    size: usize,
    tree: Box<[T]>,
}

impl<T> FenwickTree<T>
where
    T: Clone + Copy + Default + std::ops::AddAssign + std::ops::Sub<Output = T>,
{
    fn new(size: usize) -> Self {
        Self {
            size,
            tree: vec![T::default(); size + 1].into_boxed_slice(),
        }
    }
    fn update(&mut self, mut i: usize, x: T) {
        assert!(i <= self.size);
        i += 1;
        while i <= self.size {
            self.tree[i] += x;
            i += i & i.wrapping_neg();
        }
    }
    fn prefix(&self, mut i: usize) -> T {
        assert!(i <= self.size);
        let mut acc = T::default();
        while i != 0 {
            acc += self.tree[i];
            i &= i - 1;
        }
        acc
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
    let mut a = sc.read_vec::<usize>(n);
    let mut values = a.clone();
    values.sort_unstable();
    values.dedup();
    for x in a.iter_mut() {
        *x = values.partition_point(|v| v < x);
    }
    let m = values.len();
    std::mem::drop(values);
    const B: usize = 512;
    let mut queries = (0..q).map(|i| (sc.read::<usize>() - 1, sc.read::<usize>(), i)).collect::<Vec<_>>();
    queries.sort_unstable_by(|l, r| {
        let i = l.0 / B;
        let j = r.0 / B;
        i.cmp(&j).then(if i & 1 == 0 { l.1.cmp(&r.1) } else { r.1.cmp(&l.1) })
    });
    let mut fw = FenwickTree::new(m);
    let mut ans = vec![0; q];
    let mut cnt = 0;
    let mut l = queries[0].0;
    let mut r = l;
    for (ql, qr, i) in queries {
        while ql < l {
            l -= 1;
            fw.update(a[l], 1);
            cnt += fw.prefix(a[l]);
        }
        while r < qr {
            cnt += r - l - fw.prefix(a[r] + 1);
            fw.update(a[r], 1);
            r += 1;
        }
        while l < ql {
            cnt -= fw.prefix(a[l]);
            fw.update(a[l], usize::MAX);
            l += 1;
        }
        while qr < r {
            r -= 1;
            fw.update(a[r], usize::MAX);
            cnt -= r - l - fw.prefix(a[r] + 1);
        }
        ans[i] = cnt;
    }
    for x in ans {
        writeln!(out, "{x}").ok();
    }
}
