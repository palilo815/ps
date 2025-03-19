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
    let gap = sc.read::<i32>() - sc.read::<i32>();
    if gap < 0 {
        writeln!(bw, "-1 -1").ok();
        return;
    }
    let n = sc.read::<usize>();
    let mut l = vec![(0, 0); n + 1];
    let mut r = vec![(0, 0); n + 1];
    for i in 0..n {
        l[i] = (i as i32, sc.read::<i32>());
        r[i] = (i as i32, sc.read::<i32>());
    }
    l[n] = (-2, 0);
    r[n] = (-2, 0);
    l.sort_unstable_by(|l, r| l.1.cmp(&r.1));
    r.sort_unstable_by(|l, r| l.1.cmp(&r.1));
    let mut best = i32::MAX;
    let mut ans = (0, 0);
    let mut j = n;
    for (id, x) in l.into_iter() {
        while j != 0 && x + r[j - 1].1 > gap {
            j -= 1;
        }
        if x + r[j].1 <= gap || x + r[j].1 >= best {
            continue;
        }
        if id != r[j].0 {
            best = x + r[j].1;
            ans = (id, r[j].0);
        } else if j != n && x + r[j + 1].1 < best {
            best = x + r[j + 1].1;
            ans = (id, r[j + 1].0);
        }
    }
    if best == i32::MAX {
        writeln!(bw, "No").ok();
    } else {
        writeln!(bw, "{} {}", ans.0 + 1, ans.1 + 1).ok();
    }
}
