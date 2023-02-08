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
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
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
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let mut a = sc.read_vec::<u64>(n);
    a.sort_unstable();
    for _ in 0..m {
        let ans = match sc.read::<char>() {
            '1' => {
                let k = sc.read::<u64>();
                n - a.partition_point(|&x| x < k)
            }
            '2' => {
                let k = sc.read::<u64>();
                n - a.partition_point(|&x| x <= k)
            }
            _ => {
                let i = sc.read::<u64>();
                let j = sc.read::<u64>();
                a.partition_point(|&x| x <= j) - a.partition_point(|&x| x < i)
            }
        };
        writeln!(out, "{ans}").ok();
    }
}
