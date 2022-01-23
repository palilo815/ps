use std::io::Write;

#[allow(dead_code)]
mod scanner {
    use std::str::FromStr;
    pub struct Scanner<'a> {
        it: std::str::SplitWhitespace<'a>,
    }
    impl<'a> Scanner<'a> {
        pub fn new(s: &'a String) -> Scanner<'a> {
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

fn run<W: Write>(sc: &mut scanner::Scanner, out: &mut std::io::BufWriter<W>) {
    let t = sc.next::<usize>();
    for tc in 1..=t {
        let n = sc.next::<usize>();
        let m = sc.next::<usize>();
        let a = (0..n)
            .map(|_| {
                sc.next_vec::<u32>(m)
                    .into_iter()
                    .skip((m % 3 == 0) as usize)
                    .step_by(3)
                    .sum::<u32>()
            })
            .collect::<Vec<_>>();
        let ans = if a.len() % 3 == 1 {
            a.iter().step_by(3).sum::<u32>()
                - a.iter().skip(1).step_by(3).take(a.len() / 6).sum::<u32>()
                - a.iter()
                    .rev()
                    .skip(1)
                    .step_by(3)
                    .take(a.len() / 6)
                    .sum::<u32>()
        } else if a.len() % 3 == 2 {
            a.iter().step_by(3).sum::<u32>()
                - a.iter().step_by(3).take((a.len() + 1) / 6).sum::<u32>()
                - a.iter()
                    .rev()
                    .step_by(3)
                    .take((a.len() + 1) / 6)
                    .sum::<u32>()
        } else {
            a.iter().step_by(3).take((a.len() / 3 + 1) / 2).sum::<u32>()
                + a.iter()
                    .rev()
                    .step_by(3)
                    .take((a.len() / 3 + 1) / 2)
                    .sum::<u32>()
                - a.iter().skip(1).step_by(3).sum::<u32>()
        };
        writeln!(out, "Case #{}: {}", tc, ans).ok();
    }
}
