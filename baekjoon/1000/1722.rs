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

fn run<W: Write>(sc: &mut scanner::Scanner, out: &mut std::io::BufWriter<W>) {
    let n = sc.next::<usize>();
    let op = sc.next::<u32>();
    let fac = (0..n)
        .scan(1, |acc, x| {
            *acc *= if x == 0 { 1 } else { x };
            Some(*acc)
        })
        .collect::<Vec<_>>();
    let mut id = (1..=n).collect::<Vec<_>>();
    if op == 1 {
        let mut k = sc.next::<usize>() - 1;
        for cnt in fac.into_iter().rev() {
            write!(out, "{} ", id[k / cnt]).ok();
            id.remove(k / cnt);
            k %= cnt;
        }
    } else {
        let mut ans = 1;
        let permu = sc.next_vec::<usize>(n);
        for (x, cnt) in permu.into_iter().zip(fac.into_iter().rev()) {
            let i = id.iter().position(|y| *y == x).unwrap();
            ans += i * cnt;
            id.remove(i);
        }
        writeln!(out, "{}", ans).ok();
    }
}
