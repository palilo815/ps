use std::io::Write;

#[allow(dead_code)]
mod scanner {
    use std::str::FromStr;
    pub struct Scanner<'a> {
        it: std::str::SplitWhitespace<'a>,
    }
    impl<'a> Scanner<'a> {
        pub fn new(s: &'a String) -> Scanner<'a> {
            Scanner {
                it: s.split_whitespace(),
            }
        }
        pub fn next<T: FromStr>(&mut self) -> T {
            self.it.next().unwrap().parse::<T>().ok().unwrap()
        }
        pub fn next_bytes(&mut self) -> Vec<u8> {
            self.it.next().unwrap().bytes().collect()
        }
        pub fn next_chars(&mut self) -> Vec<char> {
            self.it.next().unwrap().chars().collect()
        }
        pub fn next_vec<T: FromStr>(&mut self, len: usize) -> Vec<T> {
            (0..len).map(|_| self.next()).collect()
        }
    }
}

fn main() {
    use std::io::Read;
    let mut s = String::new();
    std::io::stdin().read_to_string(&mut s).unwrap();
    let mut sc = scanner::Scanner::new(&s);
    let out = std::io::stdout();
    let mut out = std::io::BufWriter::new(out.lock());
    run(&mut sc, &mut out);
}

fn run<W: Write>(sc: &mut scanner::Scanner, out: &mut std::io::BufWriter<W>) {
    let n = sc.next::<usize>();
    let m = sc.next::<usize>();
    let mut grid = (0..n)
        .map(|_| {
            (0..m)
                .map(|_| sc.next::<i32>() + sc.next::<i32>() + sc.next::<i32>())
                .collect::<Vec<_>>()
        })
        .collect::<Vec<_>>();
    let t = sc.next::<i32>();
    let is_obj = |x| x >= t * 3;
    const MOV: [(usize, usize); 4] = [(usize::MAX, 0), (0, usize::MAX), (0, 1), (1, 0)];
    let mut stk = vec![];
    let mut ans = 0;
    for i in 0..n {
        for j in 0..m {
            if is_obj(grid[i][j]) {
                stk.push((i, j));
                grid[i][j] = -1;
                while let Some((x, y)) = stk.pop() {
                    for &(dx, dy) in MOV.iter() {
                        let xx = x.overflowing_add(dx).0;
                        let yy = y.overflowing_add(dy).0;
                        if xx != usize::MAX
                            && yy != usize::MAX
                            && xx != n
                            && yy != m
                            && is_obj(grid[xx][yy])
                        {
                            grid[xx][yy] = -1;
                            stk.push((xx, yy));
                        }
                    }
                }
                ans += 1;
            }
        }
    }
    writeln!(out, "{}", ans).ok();
}
