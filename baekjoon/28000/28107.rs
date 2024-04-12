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
    let m = sc.read::<usize>();
    let lists = (0..n)
        .map(|_| (0..sc.read()).map(|_| sc.read::<usize>()).collect::<Vec<_>>())
        .collect::<Vec<_>>();
    let mut cnt = vec![0; 200_001];
    for _ in 0..m {
        cnt[sc.read::<usize>()] += 1;
    }
    for list in lists {
        let take = list.into_iter().fold(0, |acc, i| {
            cnt[i] -= 1;
            acc + (cnt[i] >= 0) as i32
        });
        write!(out, "{take} ").ok();
    }
}
