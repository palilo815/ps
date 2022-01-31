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
    let mut a = (0..n)
        .map(|_| {
            let mut s = sc.next_bytes();
            let ext = s.iter().position(|x| *x == b'.').unwrap() + 1;
            s.drain(ext..).collect::<Vec<_>>()
        })
        .collect::<Vec<_>>();
    a.sort_unstable();
    let mut i = 0;
    while i != n {
        let i0 = i;
        while i + 1 != n && a[i] == a[i + 1] {
            i += 1;
        }
        i += 1;
        writeln!(
            out,
            "{} {}",
            String::from_utf8(a[i0].clone()).unwrap(),
            i - i0
        )
        .ok();
    }
}
