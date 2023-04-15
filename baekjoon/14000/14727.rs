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
    let mut stack = Vec::with_capacity(n);
    let mut ans = 0;
    for (i, h) in (0..).zip((0..n).map(|_| sc.read::<i32>()).chain(Some(0))) {
        while stack.last().unwrap_or(&(0, -1)).1 >= h {
            let y = stack.pop().unwrap().1;
            let x = i - stack.last().unwrap_or(&(-1, 0)).0 - 1;
            ans = ans.max(x as i64 * y as i64);
        }
        stack.push((i, h));
    }
    writeln!(out, "{ans}").ok();
}
