use std::io::Write;

#[allow(dead_code)]
mod scanner {
    use std::str::FromStr;
    pub struct Scanner<'a> {
        it: std::str::SplitWhitespace<'a>,
    }
    impl<'a> Scanner<'a> {
        pub fn new(s: &'a str) -> Scanner<'a> {
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

/*
* xoroshiro128+ 1.0
* Written in 2016-2018 by David Blackman and Sebastiano Vigna (vigna@acm.org)
* https://prng.di.unimi.it/xoroshiro128plus.c
*/
struct Random {
    s: [usize; 2],
}

impl Random {
    fn new() -> Self {
        let x = Box::into_raw(Box::new("palilo")) as usize;
        Self {
            s: [x, x.rotate_left(32)],
        }
    }
    fn next(&mut self) -> usize {
        let s0 = self.s[0];
        let mut s1 = self.s[1];
        let result = s0.wrapping_add(s1);
        s1 ^= s0;
        self.s[0] = s0.rotate_left(24) ^ s1 ^ (s1 << 16);
        self.s[1] = s1.rotate_left(37);
        result
    }
}

fn run<W: Write>(sc: &mut scanner::Scanner, out: &mut std::io::BufWriter<W>) {
    let n = sc.next::<usize>();
    let d = sc.next::<i32>();
    let d = d * d;
    let mut a = (0..n)
        .map(|i| (sc.next::<i32>(), sc.next::<i32>(), i + 1, 0))
        .collect::<Vec<_>>();
    let mut rng = Random::new();
    let mut ans = vec![];
    for _ in 0..2048 {
        a.iter_mut().for_each(|x| x.3 = rng.next());
        a.sort_unstable_by_key(|x| x.3);
        let mut res = Vec::<(i32, i32, usize, usize)>::new();
        for x in a.iter() {
            if res
                .iter()
                .all(|y| (x.0 - y.0) * (x.0 - y.0) + (x.1 - y.1) * (x.1 - y.1) <= d)
            {
                res.push(*x);
            }
        }
        if ans.len() < res.len() {
            ans = res.into_iter().map(|x| x.2).collect();
        }
    }
    writeln!(out, "{}", ans.len()).ok();
    for x in ans {
        write!(out, "{} ", x).ok();
    }
}
