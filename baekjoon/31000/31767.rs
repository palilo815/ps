use std::io::*;

struct Scanner {
    it: std::str::SplitAsciiWhitespace<'static>,
}

impl Scanner {
    fn new() -> Self {
        let mut s = String::new();
        stdin().read_to_string(&mut s).ok();
        Self {
            it: s.leak().split_ascii_whitespace(),
        }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
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
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let grass = (0..n).map(|_| (sc.read::<i32>(), sc.read::<i32>(), sc.read::<i32>())).collect::<Vec<_>>();
    let mut ord_k = (0..n).collect::<Vec<_>>();
    let mut ord_len = ord_k.clone();
    ord_k.sort_unstable_by(|&l, &r| grass[r].2.cmp(&grass[l].2));
    ord_len.sort_unstable_by(|&l, &r| (grass[r].1 - grass[r].0).cmp(&(grass[l].1 - grass[l].0)));
    let mut values = vec![0; 2 * n];
    for i in 0..n {
        values[i << 1] = grass[i].0;
        values[i << 1 | 1] = grass[i].1;
    }
    values.sort_unstable();
    values.dedup();
    let mut ls = FenwickTree::new(values.len());
    let mut rs = FenwickTree::new(values.len());
    let mut ans = vec![0; n];
    let mut j = 0;
    for i in ord_k {
        let (l, r, k) = grass[i];
        while j != n && grass[ord_len[j]].1 - grass[ord_len[j]].0 >= k {
            ls.update(values.partition_point(|&x| x < grass[ord_len[j]].0), 1);
            rs.update(values.partition_point(|&x| x < grass[ord_len[j]].1), 1);
            j += 1;
        }
        let c1 = ls.prefix(values.partition_point(|&x| x <= r - k));
        let c2 = rs.prefix(values.partition_point(|&x| x < l + k));
        ans[i] = c1 - c2 - 1;
    }
    for x in ans {
        writeln!(bw, "{x}").ok();
    }
}
