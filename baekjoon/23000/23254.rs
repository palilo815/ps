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
    let mut n = sc.next::<u32>() * 24;
    let m = sc.next::<usize>();
    let a = sc.next_vec::<u32>(m);
    let mut job = [(); 101].map(|_| vec![]);
    for i in 0..m {
        let b = sc.next::<u32>();
        job[b as usize].push((100 - a[i]) / b);
        job[((100 - a[i]) % b) as usize].push(1);
    }
    let mut ans: u32 = a.iter().sum();
    for i in (1..=100).rev() {
        for &t in job[i as usize].iter() {
            let study = u32::min(n, t);
            ans += i * study;
            n -= study;
        }
    }
    writeln!(out, "{}", ans).ok();
}
