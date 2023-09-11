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
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let mut map = std::collections::HashMap::new();
    for _ in 0..n {
        match sc.read::<usize>() {
            1 => {
                let x = sc.read::<u32>();
                let w = sc.read::<u32>();
                map.insert(w, x);
            }
            _ => {
                writeln!(out, "{}", map.get(&sc.read::<u32>()).unwrap()).ok();
            }
        }
    }
}
