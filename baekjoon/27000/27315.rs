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
    let m = sc.read::<usize>();
    let mut problems = (0..n)
        .map(|_| {
            let mut idea = sc.read::<i32>();
            let mut implement = sc.read::<i32>();
            if sc.read::<char>() == '1' {
                implement = 0;
            }
            if sc.read::<char>() == '1' {
                idea = (idea + 1) >> 1;
                implement >>= 1;
            }
            (idea, implement)
        })
        .collect::<Vec<_>>();
    problems.sort_unstable_by(|l, r| r.0.cmp(&l.0));
    let mut hd = sc.read::<i32>();
    let mut hp = sc.read::<i32>();
    let mut wa = 0;
    let mut can_solve = std::collections::BinaryHeap::new();
    for _ in 0..m {
        while let Some(&(idea, implement)) = problems.last() {
            if idea > hd {
                break;
            }
            problems.pop();
            can_solve.push(std::cmp::Reverse(implement));
        }
        if let Some(std::cmp::Reverse(implement)) = can_solve.pop() {
            wa += 0.max(implement - hp) as i64;
        } else {
            writeln!(out, "-1").ok();
            return;
        }
        hd += 1;
        hp += 1;
    }
    writeln!(out, "{wa}").ok();
}
