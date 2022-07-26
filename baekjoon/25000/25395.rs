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
    let mut s = String::new();
    stdin().read_to_string(&mut s).unwrap();
    let mut sc = Scanner::new(&s);
    let out = stdout();
    let mut out = BufWriter::new(out.lock());
    run(&mut sc, &mut out);
}

fn run<W: Write>(sc: &mut Scanner, out: &mut BufWriter<W>) {
    let n = sc.read::<usize>();
    let s = sc.read::<usize>();
    let mut x = vec![0; n + 2];
    let mut h = vec![0; n + 1];
    x[0] = i32::MIN;
    x[n + 1] = i32::MAX;
    for y in x.iter_mut().skip(1).take(n) {
        *y = sc.read::<i32>();
    }
    for y in h.iter_mut().skip(1) {
        *y = sc.read::<i32>();
    }
    let (mut l, mut r) = (s, s);
    let (mut lmax, mut rmax) = (x[s] - h[s], x[s] + h[s]);
    loop {
        let mut flag = false;
        if lmax <= x[l - 1] {
            l -= 1;
            lmax = lmax.min(x[l] - h[l]);
            rmax = rmax.max(x[l] + h[l]);
            flag = true;
        }
        if x[r + 1] <= rmax {
            r += 1;
            lmax = lmax.min(x[r] - h[r]);
            rmax = rmax.max(x[r] + h[r]);
            flag = true;
        }
        if !flag {
            break;
        }
    }
    (l..=r).for_each(|x| write!(out, "{} ", x).unwrap());
}
