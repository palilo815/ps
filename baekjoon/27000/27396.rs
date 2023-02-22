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
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let s = sc.read_bytes();
    let n = sc.read::<usize>();
    let mut table = [0; 'z' as usize + 1];
    for c in (b'A'..=b'Z').chain(b'a'..=b'z') {
        table[c as usize] = c;
    }
    for _ in 0..n {
        match sc.read::<char>() {
            '1' => {
                let u = sc.read::<char>() as u8;
                let v = sc.read::<char>() as u8;
                for c in (b'A'..=b'Z').chain(b'a'..=b'z') {
                    if table[c as usize] == u {
                        table[c as usize] = v;
                    }
                }
            }
            _ => {
                writeln!(
                    out,
                    "{}",
                    String::from_utf8(s.iter().map(|x| table[*x as usize]).collect()).unwrap()
                )
                .ok();
            }
        }
    }
}
