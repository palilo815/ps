use std::io::Write;

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
    let t = sc.next::<u32>();
    for tc in 1..=t {
        let mut s = sc.next_bytes();
        let mut cnt = [0; 26];
        s.iter().for_each(|&x| cnt[(x - b'a') as usize] += 1);
        let mx = *cnt.iter().max().unwrap();
        if mx > s.len() / 2 {
            writeln!(out, "Case #{}: IMPOSSIBLE", tc).ok();
            continue;
        }
        let mut acc = 0;
        let mut ord = vec![0; s.len()];
        for (i, &x) in cnt.iter().enumerate() {
            ord[acc..(acc + x)].fill(b'a' + i as u8);
            acc += x;
        }
        acc = 0;
        for x in cnt.iter_mut() {
            let y = *x;
            *x = acc;
            acc += y;
        }
        for x in s.iter_mut() {
            let i = (*x - b'a') as usize;
            let t = cnt[i] + mx;
            *x = ord[if t < ord.len() { t } else { t - ord.len() }];
            cnt[i] += 1;
        }
        writeln!(out, "Case #{}: {}", tc, String::from_utf8(s).unwrap()).ok();
    }
}
