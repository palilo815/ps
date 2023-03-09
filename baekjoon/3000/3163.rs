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
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let mut ants = [(0, 0); 100_000];
    let t = sc.read::<usize>();
    for _ in 0..t {
        let n = sc.read::<usize>();
        let m = sc.read::<i32>();
        let k = sc.read::<usize>() - 1;
        let ants = &mut ants[..n];
        let mut l = 0;
        let mut r = n;
        for i in 0..n {
            let p = sc.read::<i32>();
            ants[i].1 = sc.read::<i32>(); // id
            if ants[i].1 < 0 {
                ants[l].0 = p;
                l += 1;
            } else {
                r -= 1;
                ants[r].0 = m - p;
            }
        }
        r = n - 1;
        while l < r {
            let tmp = ants[l].0;
            ants[l].0 = ants[r].0;
            ants[r].0 = tmp;
            l += 1;
            r -= 1;
        }
        ants.select_nth_unstable(k);
        writeln!(out, "{}", ants[k].1).ok();
    }
}
