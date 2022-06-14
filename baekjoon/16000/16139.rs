use std::io::Write;

pub struct Scanner<'a> {
    it: std::str::SplitWhitespace<'a>,
}

impl<'a> Scanner<'a> {
    pub fn new(s: &'a str) -> Scanner<'a> {
        Scanner {
            it: s.split_whitespace(),
        }
    }
    pub fn next<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
    pub fn next_bytes(&mut self) -> Vec<u8> {
        self.it.next().unwrap().bytes().collect()
    }
}

fn main() {
    use std::io::Read;
    let mut s = String::new();
    std::io::stdin().read_to_string(&mut s).unwrap();
    let mut sc = Scanner::new(&s);
    let out = std::io::stdout();
    let mut out = std::io::BufWriter::new(out.lock());
    run(&mut sc, &mut out);
}

fn run<W: Write>(sc: &mut Scanner, out: &mut std::io::BufWriter<W>) {
    let s = sc.next_bytes();
    let mut pref = vec![[0; 26]; s.len() + 1];
    for (i, c) in s.into_iter().enumerate() {
        pref[i + 1] = pref[i];
        pref[i + 1][(c - b'a') as usize] += 1;
    }
    let q = sc.next::<usize>();
    for _ in 0..q {
        let c = sc.next::<char>() as usize - 'a' as usize;
        let l = sc.next::<usize>();
        let r = sc.next::<usize>() + 1;
        writeln!(out, "{}", pref[r][c] - pref[l][c]).ok();
    }
}
