#[allow(dead_code)]
mod scanner {
    use std::str::FromStr;
    pub struct Scanner<'a> {
        it: std::str::SplitWhitespace<'a>,
    }
    impl<'a> Scanner<'a> {
        pub fn new(s: &'a String) -> Scanner<'a> {
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

use std::io::Write;

fn main() {
    use std::io::Read;
    let mut s = String::new();
    std::io::stdin().read_to_string(&mut s).unwrap();
    let mut sc = scanner::Scanner::new(&s);
    let out = std::io::stdout();
    let mut out = std::io::BufWriter::new(out.lock());
    run(&mut sc, &mut out);
}

fn run<W: Write>(sc: &mut scanner::Scanner, out: &mut std::io::BufWriter<W>) {
    let q = sc.next::<usize>();
    let mut table = std::collections::HashMap::<Vec<u8>, std::collections::BinaryHeap<u32>>::new();
    let mut ans = 0;
    for _ in 0..q {
        let t = sc.next::<u32>();
        let s = sc.next_bytes();
        let pq = table.entry(s).or_default();
        if t == 1 {
            let k = sc.next::<usize>();
            for _ in 0..k {
                pq.push(sc.next::<u32>());
            }
        } else {
            let k = sc.next::<usize>();
            for _ in 0..k.min(pq.len()) {
                ans += pq.pop().unwrap() as u64;
            }
        }
    }
    writeln!(out, "{}", ans).ok();
}
