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
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let mut a = sc.read_vec::<i32>(n);
    let first = *a.first().unwrap();
    a.iter_mut().for_each(|x| *x -= first);
    let mut b = vec![0; n];
    for i in 1..n {
        b[i] = b[i - 1]
            + match a[i].cmp(&a[i - 1]) {
                std::cmp::Ordering::Less => -1,
                std::cmp::Ordering::Equal => 0,
                std::cmp::Ordering::Greater => 1,
            };
    }
    let mut map = std::collections::HashMap::<i32, i32>::new();
    let mut bonus = 0;
    for (a, b) in a.into_iter().zip(b.into_iter()) {
        if b != 0 {
            if a % b == 0 {
                *map.entry(a / b).or_default() += 1;
            }
        } else if a == 0 {
            bonus += 1;
        }
    }
    let ans = map.into_iter().max_by_key(|x| x.1).unwrap_or((1, 0));
    writeln!(bw, "{}\n{}", ans.1 + bonus, ans.0).ok();
}
