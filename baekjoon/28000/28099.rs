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
    let mut prev = [0; 200_001];
    let t = sc.read::<usize>();
    let mut stack = Vec::<(usize, usize)>::with_capacity(200_000);
    for _ in 0..t {
        let mut ans = "Yes";
        let n = sc.read::<usize>();
        let prev = &mut prev[..=n];
        prev.fill(usize::MAX);
        stack.clear();
        for i in 0..n {
            let x = sc.read::<usize>();
            if prev[x] != usize::MAX {
                let greatest = stack.partition_point(|e| e.1 < prev[x]);
                if greatest != stack.len() && stack[greatest].0 > x {
                    ans = "No";
                }
            }
            prev[x] = i;
            while stack.last().unwrap_or(&(usize::MAX, usize::MAX)).0 <= x {
                stack.pop();
            }
            stack.push((x, i));
        }
        writeln!(out, "{ans}").ok();
    }
}
