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
    let s = {
        let mut s = sc.read_vec::<u64>(n);
        let max_id = s.iter().enumerate().max_by_key(|(_, &x)| x).unwrap().0;
        s.rotate_left(max_id);
        s
    };
    let mut stack = Vec::with_capacity(n);
    let mut parametric = |mut lo, mut hi| {
        let mut f = |init| -> bool {
            stack.clear();
            s.iter().fold(0, |mut acc, &x| {
                if init + acc < x {
                    stack.push((acc, x));
                    0
                } else {
                    acc += x;
                    while let Some(&(add, need)) = stack.last() {
                        if init + acc < need {
                            break;
                        } else {
                            acc += add + need;
                            stack.pop();
                        }
                    }
                    acc
                }
            });
            stack.is_empty()
        };
        // first true
        while lo != hi {
            let mid = lo + (hi - lo) / 2;
            if f(mid) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        lo
    };
    writeln!(out, "{}", parametric(0, 10_000_000_000_000u64)).ok();
}
