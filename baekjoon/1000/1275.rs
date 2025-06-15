use std::io::*;

struct Scanner {
    it: std::str::SplitAsciiWhitespace<'static>,
}

impl Scanner {
    fn new() -> Self {
        let mut s = String::new();
        stdin().read_to_string(&mut s).ok();
        Self { it: s.leak().split_ascii_whitespace() }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
    }
}

struct BinaryIndexedTree<T, F> {
    size: usize,
    data: Box<[T]>,
    e: T,
    f: F,
}

impl<T, F> BinaryIndexedTree<T, F>
where
    T: Copy,
    F: Fn(T, T) -> T,
{
    fn from(arr: &[T], e: T, f: F) -> Self {
        let size = arr.len();
        let mut data = vec![e; size + 1].into_boxed_slice();
        data[1..].copy_from_slice(arr);
        for i in 1..size {
            let j = i + (i & i.wrapping_neg());
            if j <= size {
                data[j] = f(data[i], data[j]);
            }
        }
        Self { size, data, e, f }
    }
    fn update(&mut self, mut i: usize, v: T) {
        assert!(i <= self.size);
        i += 1;
        while i <= self.size {
            self.data[i] = (self.f)(v, self.data[i]);
            i += i & i.wrapping_neg();
        }
    }
    fn prefix(&self, mut i: usize) -> T {
        assert!(i <= self.size);
        let mut ret = self.e;
        while i != 0 {
            ret = (self.f)(ret, self.data[i]);
            i &= i - 1;
        }
        ret
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let mut data = sc.read_vec::<i64>(n);
    let mut bit = BinaryIndexedTree::from(&data, 0, std::ops::Add::add);
    for _ in 0..m {
        let l = sc.read::<usize>();
        let r = sc.read::<usize>();
        writeln!(bw, "{}", bit.prefix(l.max(r)) - bit.prefix(l.min(r) - 1)).ok();
        let a = sc.read::<usize>() - 1;
        let b = sc.read::<i64>();
        let diff = b - std::mem::replace(&mut data[a], b);
        bit.update(a, diff);
    }
}
