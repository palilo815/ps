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
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    const N: usize = 200_000;
    let z = sc.read::<usize>();
    let mut a = vec![0; N];
    let mut suff = vec![0; N];
    let mut lis = Vec::with_capacity(N);
    for _ in 0..z {
        let n = sc.read::<usize>();
        let a = &mut a[..n];
        let suff = &mut suff[..n];
        for x in a.iter_mut() {
            *x = sc.read::<u32>();
        }
        suff[n - 1] = 1;
        for i in (1..n).rev() {
            suff[i - 1] = if a[i - 1] < a[i] { suff[i] + 1 } else { 1 };
        }
        let mut pref = 0;
        let mut ans = 0;
        lis.clear();
        for i in 0..n {
            pref = if i != 0 && a[i - 1] < a[i] { pref + 1 } else { 0 };
            if pref == lis.len() {
                lis.push(a[i]);
            } else {
                lis[pref] = lis[pref].min(a[i]);
            }
            let best = lis.partition_point(|&v| v < a[i]) as u32 + suff[i];
            ans = ans.max(best);
        }
        writeln!(out, "{ans}").ok();
    }
}
