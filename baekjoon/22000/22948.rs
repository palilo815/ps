use std::io::*;

struct Scanner {
    it: std::str::SplitAsciiWhitespace<'static>,
}

impl Scanner {
    fn new() -> Self {
        let mut buf = Vec::new();
        stdin().lock().read_to_end(&mut buf).ok();
        let s = unsafe { std::str::from_utf8_unchecked(Box::leak(buf.into_boxed_slice())) };
        Self { it: s.split_ascii_whitespace() }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let mut events = vec![(0, 0); n << 1];
    for i in 0..n {
        let id = sc.read::<i32>();
        let x = sc.read::<i32>();
        let r = sc.read::<i32>();
        events[i << 1] = (!id, x - r);
        events[i << 1 | 1] = (id, x + r);
    }
    events.sort_unstable_by(|l, r| l.1.cmp(&r.1));
    let mut stack = Vec::with_capacity(n + 1);
    stack.push(0);
    let mut par = vec![0; n + 1];
    par[0] = usize::MAX;
    for (id, _) in events {
        if id < 0 {
            par[!id as usize] = *stack.last().unwrap() as usize;
            stack.push(!id);
        } else {
            stack.pop();
        }
    }
    let mut a = sc.read::<usize>();
    let mut b = sc.read::<usize>();
    let mut path_a = Vec::with_capacity(n + 1);
    let mut path_b = Vec::with_capacity(n + 1);
    while par[a] != usize::MAX {
        path_a.push(a);
        a = par[a];
    }
    while par[b] != usize::MAX {
        path_b.push(b);
        b = par[b];
    }
    while path_a.last() == path_b.last() {
        path_a.pop();
        path_b.pop();
    }
    writeln!(bw, "{}", path_a.len() + path_b.len() + 1).ok();
    for x in path_a {
        write!(bw, "{x} ").ok();
    }
    write!(bw, "{}", par[*path_b.last().unwrap()]).ok();
    for x in path_b.into_iter().rev() {
        write!(bw, " {x}").ok();
    }
}
