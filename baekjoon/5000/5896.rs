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
    let n = sc.read::<usize>();
    let k = sc.read::<usize>();
    let mut m = sc.read::<i64>();
    let cow = (0..n).map(|_| (sc.read::<i32>(), sc.read::<i32>())).collect::<Vec<_>>();
    let mut pid = (0..n).collect::<Vec<_>>();
    let mut cid = (0..n).collect::<Vec<_>>();
    pid.sort_unstable_by_key(|&i| cow[i].0);
    cid.sort_unstable_by_key(|&i| cow[i].1);
    let mut used = vec![false; n];
    let mut pq = (0..k).map(|_| std::cmp::Reverse(0)).collect::<std::collections::BinaryHeap<_>>();
    let mut pit = pid.into_iter().peekable();
    let mut cit = cid.into_iter().peekable();
    let mut ans = 0;
    while ans != n {
        while used[*pit.peek().unwrap()] {
            pit.next();
        }
        while used[*cit.peek().unwrap()] {
            cit.next();
        }
        let p_cow = cow[*pit.peek().unwrap()];
        let c_cow = cow[*cit.peek().unwrap()];
        let undo = pq.peek().unwrap().0;
        if c_cow.1 + undo < p_cow.0 {
            m -= (c_cow.1 + undo) as i64;
            *pq.peek_mut().unwrap() = std::cmp::Reverse(c_cow.0 - c_cow.1);
            used[cit.next().unwrap()] = true;
        } else {
            m -= p_cow.0 as i64;
            used[pit.next().unwrap()] = true;
        }
        if m < 0 {
            break;
        }
        ans += 1;
    }
    writeln!(bw, "{ans}").ok();
}
