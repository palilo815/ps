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
    fn raw(&mut self) -> &str {
        self.it.next().unwrap()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    const N: usize = 30;
    const MOVE: [(usize, usize); 4] = [(usize::MAX, 0), (0, usize::MAX), (0, 1), (1, 0)];
    let mut check = [[false; N]; N];
    let mut stack = vec![];
    let t = sc.read::<usize>();
    for t in 1..=t {
        let n = sc.read::<usize>();
        let m = sc.read::<usize>();
        let p = sc.read::<usize>();
        let q = sc.read::<usize>();
        check.fill([false; N]);
        for _ in 0..q {
            let mut x = 0;
            let mut y = 0;
            check[x][y] = true;
            for c in sc.raw().bytes() {
                match c {
                    b'd' => x -= 1,
                    b'u' => x += 1,
                    b'l' => y -= 1,
                    b'r' => y += 1,
                    _ => unreachable!(),
                }
                check[x][y] = true;
            }
        }
        let mut ans = 0;
        for i in 0..n {
            for j in 0..m {
                if check[i][j] {
                    continue;
                }
                check[i][j] = true;
                stack.push((i, j));
                let mut size = 0;
                while let Some((x, y)) = stack.pop() {
                    size += 1;
                    for &(dx, dy) in MOVE.iter() {
                        let x = x + dx;
                        let y = y + dy;
                        if x < n && y < m && !check[x][y] {
                            check[x][y] = true;
                            stack.push((x, y));
                        }
                    }
                }
                ans += (size >= p) as i32;
            }
        }
        writeln!(bw, "Data Set {t}:\n{ans}\n").ok();
    }
}
