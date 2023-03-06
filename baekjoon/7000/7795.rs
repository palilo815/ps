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
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let mut a = [0; 20_000];
    let t = sc.read::<usize>();
    for _ in 0..t {
        let n = sc.read::<usize>();
        let m = sc.read::<usize>();
        let a = &mut a[..n];
        for x in a.iter_mut() {
            *x = sc.read::<u32>();
        }
        a.sort_unstable_by(|l, r| r.cmp(l));
        let ans = (0..m).fold(0, |acc, _| {
            let b = sc.read::<u32>();
            acc + a.partition_point(|&a| a > b)
        });
        writeln!(out, "{ans}").ok();
    }
}
