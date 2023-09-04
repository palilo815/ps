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
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let k = sc.read::<usize>();
    let a = sc.read_vec::<u32>(n);
    let mut ans = a.iter().sum::<u32>();
    if n == k {
        writeln!(out, "{ans}").ok();
        return;
    }
    let mut pq = std::collections::BinaryHeap::with_capacity(n);
    pq.extend(a.iter().rev().take(n % (k + 1)));
    for chunk in a.chunks_exact(k + 1).rev() {
        pq.push(chunk[k]);
        ans -= pq.pop().unwrap();
        pq.extend(chunk.iter().take(k));
    }
    writeln!(out, "{ans}").ok();
}
