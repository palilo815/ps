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
    let k = sc.read::<usize>();
    let mut q = (1..=n as u32).collect::<Vec<_>>();
    let mut head = 0;
    let mut tail = 0;
    let mut size = n;
    loop {
        if size <= k {
            writeln!(out, "{}", q[head]).ok();
            break;
        }
        q[tail] = q[head];
        head = (head + k) % n;
        tail = (tail + 1) % n;
        size -= k - 1;
    }
}
