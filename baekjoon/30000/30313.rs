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
    let k = n.min(sc.read::<usize>());
    let mut pq = (0..k)
        .map(|_| std::cmp::Reverse(sc.read::<u32>()))
        .collect::<std::collections::BinaryHeap<_>>();
    let mut ans = 0;
    let mut prv = 0;
    for i in 0..n {
        let cur = pq.pop().unwrap().0;
        if i + k < n {
            pq.push(std::cmp::Reverse(cur + sc.read::<u32>()));
        }
        ans = ans.max(cur - prv);
        prv = cur;
    }
    writeln!(out, "{ans}").ok();
}
