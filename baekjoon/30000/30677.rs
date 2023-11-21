use std::io::*;

struct Scanner<'a> {
    it: std::str::SplitWhitespace<'a>,
}

impl<'a> Scanner<'a> {
    fn new(s: &str) -> Scanner {
        Scanner {
            it: s.split_whitespace(),
        }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
    }
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let k = sc.read::<usize>();
    let c = sc.read::<i64>();
    let r = sc.read::<i32>();
    let base = sc.read_vec::<i32>(k);
    let s = sc.read_vec::<i32>(k);
    let p = sc.read_vec::<i32>(k);
    let mut fat = 0;
    let mut combo = 0;
    let mut star = 0;
    let mut skill = vec![0; k];
    for _ in 0..n {
        let l = sc.read::<usize>() - 1;
        if l == usize::MAX {
            fat = 0.max(fat - r);
            combo = 0;
        } else {
            star += base[l] as i64 * (100 + combo * c) * (100 + skill[l] as i64 * s[l] as i64) / 10000;
            combo += 1;
            skill[l] += 1;
            fat += p[l];
            if fat > 100 {
                writeln!(out, "-1").ok();
                return;
            }
        }
    }
    writeln!(out, "{star}").ok();
}
