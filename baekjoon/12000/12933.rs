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
    let s = sc.read_bytes();
    let mut cnt = [0; 5];
    for x in s.into_iter() {
        let i = match x {
            b'q' => 0,
            b'u' => 1,
            b'a' => 2,
            b'c' => 3,
            _ => 4,
        };
        cnt[i] += 1;
        if i == 0 {
            cnt[4] -= (cnt[4] != 0) as i32;
        } else if cnt[i - 1] == 0 {
            cnt[4] = -1;
            break;
        } else {
            cnt[i - 1] -= 1;
        }
    }
    if cnt.iter().take(4).any(|&x| x != 0) {
        cnt[4] = -1;
    }
    writeln!(out, "{}", cnt[4]).ok();
}
