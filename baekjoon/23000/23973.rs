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
    fn read_bytes(&mut self) -> Vec<u8> {
        self.it.next().unwrap().bytes().collect()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let grid = (0..n).map(|_| sc.read_bytes()).collect::<Vec<_>>();
    for i in 0..n {
        for j in 0..m {
            if grid[i][j] == b'0' {
                continue;
            }
            let mut check = 0;
            'outer: for i2 in (i.max(9) - 9)..n.min(i + 10) {
                for j2 in (j.max(9) - 9)..m.min(j + 10) {
                    if grid[i2][j2] == b'1' {
                        let bit = 1 << std::cmp::max(((i - i2) as isize).abs(), ((j - j2) as isize).abs());
                        if (check & bit) == 0 {
                            check |= bit;
                        } else {
                            check = 0;
                            break 'outer;
                        }
                    }
                }
            }
            if check == (1 << 10) - 1 {
                writeln!(bw, "{i} {j}").ok();
                return;
            }
        }
    }
    writeln!(bw, "-1").ok();
}
