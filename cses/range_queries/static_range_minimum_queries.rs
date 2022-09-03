use std::io::*;

struct Scanner<'a> {
    it: std::str::SplitWhitespace<'a>,
}

impl<'a> Scanner<'a> {
    fn new(s: &'a str) -> Scanner<'a> {
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

fn main() {
    let mut s = String::new();
    stdin().read_to_string(&mut s).unwrap();
    let mut sc = Scanner::new(&s);
    let out = stdout();
    let mut out = BufWriter::new(out.lock());
    run(&mut sc, &mut out);
}

pub struct SparseTable<T, F> {
    size: usize,
    table: Vec<Vec<T>>,
    op: F,
}

impl<T, F> SparseTable<T, F>
where
    F: Fn(&T, &T) -> T,
{
    pub fn new(a: Vec<T>, op: F) -> Self {
        let size = a.len();
        let mut table =
            Vec::with_capacity(8 * std::mem::size_of::<usize>() - size.leading_zeros() as usize);
        table.push(a);
        let mut k = 1;
        for i in 1..table.capacity() {
            table.push(
                table[i - 1]
                    .windows(k + 1)
                    .map(|x| op(&x[0], &x[k]))
                    .collect(),
            );
            k <<= 1;
        }
        SparseTable { size, table, op }
    }
    pub fn product(&self, l: usize, r: usize) -> T {
        assert!(l < r && r <= self.size);
        let k = (8 * std::mem::size_of::<usize>() - 1) ^ (r - l).leading_zeros() as usize;
        (self.op)(&self.table[k][l], &self.table[k][r - (1 << k)])
    }
}

fn run<W: Write>(sc: &mut Scanner, out: &mut BufWriter<W>) {
    let n = sc.read::<usize>();
    let q = sc.read::<usize>();
    let sparse = SparseTable::new(sc.read_vec::<u32>(n), |lhs, rhs| *lhs.min(rhs));
    for _ in 0..q {
        let l = sc.read::<usize>() - 1;
        let r = sc.read::<usize>();
        writeln!(out, "{}", sparse.product(l, r)).ok();
    }
}
