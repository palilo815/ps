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
        let mut x = (9 - s.iter().fold(0, |acc, x| acc + (x - b'0') as i32)) % 9;
        if x < 0 {
            x += 9;
        }
        let mut i = 0;
        if x == 0 {
            i += 1;
        }
        while i != s.len() && ((s[i] - b'0') as i32) <= x {
            i += 1;
        }
        writeln!(
            out,
            "Case #{}: {}{}{}",
            tc + 1,
            String::from_utf8(s[..i].to_vec()).unwrap(),
            x,
            String::from_utf8(s[i..].to_vec()).unwrap()
        )
        .ok();
    }
}
