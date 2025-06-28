use std::io::*;

struct Scanner {
    it: std::str::SplitAsciiWhitespace<'static>,
}

impl Scanner {
    fn new() -> Self {
        let mut s = String::new();
        stdin().read_to_string(&mut s).ok();
        Self { it: s.leak().split_ascii_whitespace() }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    const P: usize = 100;
    let mut mileage = [0; P];
    let n = sc.read::<usize>();
    let mut m = sc.read::<i32>();
    let mut a = (0..n)
        .map(|_| {
            let p = sc.read::<usize>();
            let l = sc.read::<usize>();
            let mileage = &mut mileage[..p];
            mileage.fill_with(|| sc.read::<i32>());
            if p < l {
                1
            } else {
                mileage.select_nth_unstable_by(l - 1, |l, r| r.cmp(l));
                mileage[l - 1]
            }
        })
        .collect::<Vec<_>>();
    a.sort_unstable();
    let mut i = 0;
    while i != n {
        m -= a[i];
        if m < 0 {
            break;
        }
        i += 1;
    }
    writeln!(bw, "{i}").ok();
}
