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
}

fn merge_sort(data: &mut [u32], buf: &mut [u32]) -> i64 {
    if data.len() < 2 {
        return 0;
    }
    let (l, r) = data.split_at_mut(data.len() / 2);
    let (lbuf, rbuf) = buf.split_at_mut(buf.len() / 2);
    let mut inv = merge_sort(l, lbuf) + merge_sort(r, rbuf);
    let mut it = buf.iter_mut();
    let mut l = l.iter().peekable();
    let mut r = r.iter().peekable();
    let mut cnt = l.len() as i64;
    while l.peek().is_some() || r.peek().is_some() {
        if l.peek().unwrap_or(&&u32::MAX) > r.peek().unwrap_or(&&u32::MAX) {
            *it.next().unwrap() = *r.next().unwrap();
            inv += cnt;
        } else {
            *it.next().unwrap() = *l.next().unwrap();
            cnt -= 1;
        }
    }
    data.copy_from_slice(buf);
    inv
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    const N: usize = 100_000;
    let mut a = vec![0; N];
    let mut buf = vec![0; N];
    loop {
        let n = sc.read::<usize>();
        if n == 0 {
            break;
        }
        let a = &mut a[..n];
        for x in a.iter_mut() {
            *x = sc.read::<u32>();
        }
        let buf = &mut buf[..n];
        let inv = merge_sort(a, buf);
        writeln!(out, "{}", if inv & 1 == 1 { "Marcelo" } else { "Carlos" }).ok();
    }
}
