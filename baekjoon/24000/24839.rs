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
    fn read_bytes(&mut self) -> Vec<u8> {
        self.it.next().unwrap().bytes().collect()
    }
}

fn main() {
    let mut s = String::new();
    stdin().read_to_string(&mut s).unwrap();
    let mut sc = Scanner::new(&s);
    let out = stdout();
    let mut out = BufWriter::new(out.lock());
    run(&mut sc, &mut out);
}

fn run<W: Write>(sc: &mut Scanner, out: &mut BufWriter<W>) {
    let t = sc.read::<usize>();
    for tc in 0..t {
        let s = sc.read_bytes();
        let t = sc.read_bytes();
        let mut diff = t.len() - s.len();
        let mut i = 0;
        for x in s.into_iter() {
            while i != t.len() && x != t[i] {
                i += 1;
            }
            if i == t.len() {
                diff = usize::MAX;
                break;
            }
            i += 1;
        }
        writeln!(
            out,
            "Case #{}: {}",
            tc + 1,
            if diff == usize::MAX {
                String::from("IMPOSSIBLE")
            } else {
                diff.to_string()
            }
        )
        .ok();
    }
}
