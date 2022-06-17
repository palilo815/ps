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
    const MAX: usize = 65536;
    let n = sc.read::<usize>();
    let k = sc.read::<usize>();
    let mut circular_queue = sc.read_vec::<usize>(k);
    let half = (k as i32 + 1) / 2;
    let mut bit = [0; MAX + 1];
    let add = |bit: &mut [i32], mut i: usize| {
        i += 1;
        while i <= MAX {
            bit[i] += 1;
            i += i & i.wrapping_neg();
        }
    };
    let sub = |bit: &mut [i32], mut i: usize| {
        i += 1;
        while i <= MAX {
            bit[i] -= 1;
            i += i & i.wrapping_neg();
        }
    };
    let get_med = |bit: &[i32]| {
        let mut i = 0;
        let mut x = half;
        let mut pw = MAX;
        while pw != 0 {
            if (i | pw) <= MAX && bit[i | pw] < x {
                i |= pw;
                x -= bit[i];
            }
            pw >>= 1;
        }
        i
    };
    for &i in circular_queue.iter() {
        add(&mut bit, i);
    }
    let mut ans = get_med(&bit) as i64;
    for i in 0..(n - k) {
        sub(&mut bit, circular_queue[i % k]);
        circular_queue[i % k] = sc.read::<usize>();
        add(&mut bit, circular_queue[i % k]);
        ans += get_med(&bit) as i64;
    }
    writeln!(out, "{}", ans).ok();
}
