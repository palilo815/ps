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
    let mut dancer = std::collections::HashSet::new();
    dancer.insert(String::from("ChongChong"));
    let n = sc.read::<usize>();
    for _ in 0..n {
        let a = sc.read::<String>();
        let b = sc.read::<String>();
        if dancer.get(&a).is_some() || dancer.get(&b).is_some() {
            dancer.insert(a);
            dancer.insert(b);
        }
    }
    writeln!(out, "{}", dancer.len()).ok();
}
