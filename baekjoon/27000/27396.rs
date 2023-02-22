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
    fn read_chars(&mut self) -> Vec<char> {
        self.it.next().unwrap().chars().collect()
    }
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let s = sc.read_chars();
    let n = sc.read::<usize>();
    let mut table = ['?'; 'z' as usize + 1];
    for c in ('A'..='Z').chain('a'..='z') {
        table[c as usize] = c;
    }
    for _ in 0..n {
        match sc.read::<char>() {
            '1' => {
                let u = sc.read::<char>();
                let v = sc.read::<char>();
                for c in ('A'..='Z').chain('a'..='z') {
                    if table[c as usize] == u {
                        table[c as usize] = v;
                    }
                }
            }
            _ => {
                s.iter().for_each(|&x| {
                    write!(out, "{}", table[x as usize]).ok();
                });
                writeln!(out).ok();
            }
        }
    }
}
