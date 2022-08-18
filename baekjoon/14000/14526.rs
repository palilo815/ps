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
    let mut colour = vec![0; n + 2];
    for c in colour.iter_mut().skip(1).take(n) {
        *c = sc.read::<usize>();
    }
    let mut intervals = vec![(usize::MAX, usize::MAX); n + 1];
    for (i, &c) in colour.iter().enumerate() {
        if intervals[c].0 == usize::MAX {
            intervals[c] = (i, i);
        } else {
            intervals[c].1 = i;
        }
    }
    let mut stack = Vec::with_capacity(n + 1);
    let mut ans = 0;
    for (i, c) in colour.into_iter().enumerate() {
        if i == intervals[c].0 {
            stack.push(c);
            ans = ans.max(stack.len());
        }
        if *stack.last().unwrap_or(&usize::MAX) != c {
            writeln!(out, "-1").ok();
            return;
        }
        if i == intervals[c].1 {
            stack.pop();
        }
    }
    writeln!(out, "{}", ans - 1).ok();
}
