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
    let mut a = (0..n).map(|_| (sc.read::<u32>(), sc.read::<u32>())).collect::<Vec<_>>();
    a.sort_unstable();
    let ans = a
        .into_iter()
        .rev()
        .fold(
            (0, 0),
            |(acc, mx), (_, x)| {
                if x > mx {
                    (acc + 1, x)
                } else {
                    (acc, mx)
                }
            },
        )
        .0;
    writeln!(out, "{ans}").ok();
}
