use std::io::Write;

#[allow(dead_code)]
mod scanner {
    use std::str::FromStr;
    pub struct Scanner<'a> {
        it: std::str::SplitWhitespace<'a>,
    }
    impl<'a> Scanner<'a> {
        pub fn new(s: &'a str) -> Scanner<'a> {
            Scanner {
                it: s.split_whitespace(),
            }
        }
        pub fn next<T: FromStr>(&mut self) -> T {
            self.it.next().unwrap().parse::<T>().ok().unwrap()
        }
        pub fn next_bytes(&mut self) -> Vec<u8> {
            self.it.next().unwrap().bytes().collect()
        }
        pub fn next_chars(&mut self) -> Vec<char> {
            self.it.next().unwrap().chars().collect()
        }
        pub fn next_vec<T: FromStr>(&mut self, len: usize) -> Vec<T> {
            (0..len).map(|_| self.next()).collect()
        }
    }
}

fn main() {
    use std::io::Read;
    let mut s = String::new();
    std::io::stdin().read_to_string(&mut s).unwrap();
    let mut sc = scanner::Scanner::new(&s);
    let out = std::io::stdout();
    let mut out = std::io::BufWriter::new(out.lock());
    run(&mut sc, &mut out);
}

pub struct BinaryIndexedTree<T> {
    size: usize,
    tree: Vec<T>,
    id: T,
}

#[allow(dead_code)]
impl<T> BinaryIndexedTree<T>
where
    T: std::clone::Clone + std::cmp::Ord + std::marker::Copy,
{
    pub fn new(size: usize, id: T) -> Self {
        Self {
            size,
            tree: vec![id; size + 1],
            id,
        }
    }
    pub fn update(&mut self, mut i: usize, x: T) {
        assert!(i <= self.size);
        i += 1;
        while i <= self.size {
            self.tree[i] = x.max(self.tree[i]);
            i += i & i.wrapping_neg();
        }
    }
    pub fn prefix(&self, mut i: usize) -> T {
        assert!(i <= self.size);
        let mut ret = self.id;
        while i != 0 {
            ret = ret.max(self.tree[i]);
            i &= i - 1;
        }
        ret
    }
}

fn run<W: Write>(sc: &mut scanner::Scanner, out: &mut std::io::BufWriter<W>) {
    let n = sc.next::<usize>();
    let m = sc.next::<usize>();
    let mut a = (0..n)
        .map(|_| (sc.next::<u32>(), sc.next::<u32>()))
        .collect::<Vec<_>>();
    let mut q = (0..m)
        .map(|i| (sc.next::<u32>(), sc.next::<u32>(), i))
        .collect::<Vec<_>>();
    let coordis = {
        let mut ys = a
            .iter()
            .map(|x| x.1)
            .chain(q.iter().map(|x| x.1))
            .collect::<Vec<_>>();
        ys.sort_unstable();
        ys.dedup();
        let l = ys.len();
        a.iter_mut()
            .for_each(|(_, y)| *y = ys.binary_search(y).unwrap_or(l) as u32);
        q.iter_mut()
            .for_each(|(_, y, _)| *y = ys.binary_search(y).unwrap_or(l) as u32);
        l
    };
    a.sort_unstable_by(|lhs, rhs| match rhs.0.cmp(&lhs.0) {
        std::cmp::Ordering::Equal => lhs.1.cmp(&rhs.1),
        other => other,
    });
    q.sort_unstable_by(|lhs, rhs| rhs.0.cmp(&lhs.0));
    let mut bit = BinaryIndexedTree::new(coordis, 0);
    let mut ans = vec![0; m];
    let (mut i, mut j) = (0, 0);
    while i != a.len() || j != q.len() {
        if i == a.len() || j != q.len() && q[j].0 > a[i].0 {
            ans[q[j].2] = bit.prefix(q[j].1 as usize + 1);
            j += 1;
        } else {
            let dp = bit.prefix(a[i].1 as usize + 1);
            bit.update(a[i].1 as usize, dp + 1);
            i += 1;
        }
    }
    for x in ans {
        writeln!(out, "{}", x).ok();
    }
}
