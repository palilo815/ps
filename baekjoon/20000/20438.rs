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
    let n = sc.next::<usize>();
    let k = sc.next::<usize>();
    let q = sc.next::<usize>();
    let m = sc.next::<usize>();
    // id = [0, n + 3)
    let mut sleeping = vec![false; n + 3];
    for _ in 0..k {
        sleeping[sc.next::<usize>()] = true;
    }
    let mut attend = vec![false; n + 3];
    for _ in 0..q {
        let i = sc.next::<usize>();
        if sleeping[i] {
            continue;
        }
        for j in (i..(n + 3)).step_by(i) {
            if !sleeping[j] {
                attend[j] = true;
            }
        }
    }
    let mut pref = vec![0; n + 4];
    for i in 3..(n + 3) {
        pref[i + 1] = pref[i] + if attend[i] { 0 } else { 1 };
    }
    for _ in 0..m {
        let l = sc.next::<usize>();
        let r = sc.next::<usize>() + 1;
        writeln!(out, "{}", pref[r] - pref[l]).ok();
    }
}
