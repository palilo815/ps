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
    let t = sc.next::<usize>();
    for _ in 0..t {
        run(&mut sc, &mut out);
    }
}

fn run<W: Write>(sc: &mut scanner::Scanner, out: &mut std::io::BufWriter<W>) {
    let mut a = [0; 4];
    let mut b = [0; 4];
    let mut c = [0; 4];
    for x in a.iter_mut() {
        *x = sc.next::<u32>();
    }
    for x in b.iter_mut() {
        *x = sc.next::<u32>();
    }
    let solve = |a: &[u32], b: &[u32]| -> i32 {
        let mut a_vs_b = 0;
        for x in a.iter() {
            for y in b.iter() {
                a_vs_b += match x.cmp(y) {
                    std::cmp::Ordering::Less => -1,
                    std::cmp::Ordering::Greater => 1,
                    std::cmp::Ordering::Equal => 0,
                };
            }
        }
        a_vs_b
    };
    let a_vs_b = solve(&a, &b);
    if a_vs_b == 0 {
        writeln!(out, "no").ok();
        return;
    }
    if a_vs_b < 0 {
        std::mem::swap(&mut a, &mut b);
    }
    for w in 1..11 {
        c[0] = w;
        for x in 1..11 {
            c[1] = x;
            for y in 1..11 {
                c[2] = y;
                for z in 1..11 {
                    c[3] = z;
                    let b_vs_c = solve(&b, &c);
                    let c_vs_a = solve(&c, &a);
                    if b_vs_c.is_positive() && c_vs_a.is_positive() {
                        writeln!(out, "yes").ok();
                        return;
                    }
                }
            }
        }
    }
    writeln!(out, "no").ok();
}
