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
    let n = sc.read::<u32>();
    let m = sc.read::<u32>();
    let t = sc.read::<usize>();
    let mut cur = std::collections::HashMap::new();
    let mut nxt = std::collections::HashMap::new();
    for _ in 0..t {
        let i = sc.read::<u32>();
        let entry = cur.entry(i).or_default();
        *entry = m.min(*entry + sc.read::<u32>());
        let mut acc = 0;
        for (key, val) in cur.iter() {
            let val2 = val / 5;
            if val2 == 0 {
                continue;
            }
            for key2 in 1.max(key - 1)..=n.min(key + 1) {
                let entry = nxt.entry(key2).or_insert(0);
                *entry += val2;
                acc += val2;
            }
        }
        cur.clear();
        std::mem::swap(&mut cur, &mut nxt);
        writeln!(bw, "{acc}").ok();
    }
}
