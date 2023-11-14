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

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let mut points = (0..n).map(|_| (sc.read::<i32>(), sc.read::<i32>())).collect::<Vec<_>>();
    points.sort_unstable_by(|l, r| (l.0.abs() + l.1.abs()).cmp(&(r.0.abs() + r.1.abs())));
    let mut set = points.clone().into_iter().collect::<std::collections::HashSet<_>>();
    let mut stack = vec![];
    const MOVE: [(i32, i32); 8] = [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)];
    let mut ans = 0;
    let mut prv = 0;
    for p in points {
        if set.remove(&p) {
            let d = (p.0.abs() + p.1.abs()) as i64;
            ans += d + prv;
            prv = d;
            stack.push(p);
            while let Some((x, y)) = stack.pop() {
                for &(dx, dy) in MOVE.iter() {
                    let x = x + dx;
                    let y = y + dy;
                    if set.remove(&(x, y)) {
                        stack.push((x, y));
                    }
                }
            }
        }
    }
    writeln!(out, "{ans}").ok();
}
