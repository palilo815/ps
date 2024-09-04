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
    let m = sc.read::<usize>();
    let mut sum = vec![0; n];
    let mut top2 = vec![[(0, 0), (0, 0)]; n];
    let mut hash_map = std::collections::HashMap::new();
    for _ in 0..m {
        let u = sc.read::<usize>() - 1;
        let v = sc.read::<usize>() - 1;
        let p = sc.read::<u64>();
        let insert = |arr: &mut [(u64, usize); 2], x: (u64, usize)| {
            if x > arr[0] {
                arr[1] = arr[0];
                arr[0] = x;
            } else if x > arr[1] {
                arr[1] = x;
            }
        };
        insert(&mut top2[u], (p, v));
        insert(&mut top2[v], (p, u));
        sum[u] += p;
        sum[v] += p;
        hash_map.insert((u.min(v), u.max(v)), p);
    }
    let mut ans = sum.into_iter().max().unwrap();
    for [(p1, u), (p2, v)] in top2 {
        if p2 != 0 {
            if let Some(&p3) = hash_map.get(&(u.min(v), u.max(v))) {
                ans = ans.max(p1 + p2 + p3);
            }
        }
    }
    writeln!(bw, "{ans}").ok();
}
