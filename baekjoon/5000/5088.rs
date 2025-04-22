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
    const N: usize = 100;
    let mut map = [0; N * N];
    loop {
        let rows = sc.read::<usize>();
        let cols = sc.read::<usize>();
        if rows == 0 && cols == 0 {
            break;
        }
        map.fill(0);
        let n = sc.read::<usize>();
        for _ in 0..n {
            let x = sc.read::<usize>();
            let y = sc.read::<usize>();
            map[100 * x + y] += 1;
        }
        let n = sc.read::<usize>();
        let ans = (0..n)
            .map(|_| {
                let x = sc.read::<usize>();
                let y = sc.read::<usize>();
                map[100 * x + y]
            })
            .sum::<i32>();
        writeln!(bw, "{ans}").ok();
    }
}
