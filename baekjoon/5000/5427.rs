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
    const N: usize = 1_000;
    const MOVE: [(usize, usize); 4] = [(usize::MAX, 0), (0, usize::MAX), (0, 1), (1, 0)];
    const MAN: u8 = b'@';
    const WALL: u8 = b'#';
    const EMPTY: u8 = b'.';
    let mut mat = vec![vec![0; N]; N];
    let mut man = std::collections::VecDeque::new();
    let mut fire = std::collections::VecDeque::new();
    let t = sc.read::<usize>();
    for _ in 0..t {
        man.clear();
        fire.clear();
        let m = sc.read::<usize>();
        let n = sc.read::<usize>();
        mat.iter_mut().take(n).for_each(|row| row[..m].copy_from_slice(sc.raw().as_bytes()));
        for (i, row) in mat.iter().take(n).enumerate() {
            for (j, &x) in row.iter().take(m).enumerate() {
                match x {
                    MAN => man.push_back((i, j)),
                    b'*' => fire.push_back((i, j)),
                    _ => {}
                }
            }
        }
        assert_eq!(man.len(), 1);
        let mut ans = 0;
        'outer: for i in 1.. {
            for _ in 0..fire.len() {
                let (x, y) = fire.pop_front().unwrap();
                for (x, y) in MOVE.iter().map(|d| (x + d.0, y + d.1)) {
                    if x < n && y < m && mat[x][y] != WALL {
                        mat[x][y] = WALL;
                        fire.push_back((x, y));
                    }
                }
            }
            for _ in 0..man.len() {
                let (x, y) = man.pop_front().unwrap();
                for (x, y) in MOVE.iter().map(|d| (x + d.0, y + d.1)) {
                    if x >= n || y >= m {
                        ans = i;
                        break 'outer;
                    }
                    if mat[x][y] == EMPTY {
                        mat[x][y] = MAN;
                        man.push_back((x, y));
                    }
                }
            }
            if man.is_empty() {
                break;
            }
        }
        match ans {
            0 => writeln!(bw, "IMPOSSIBLE").ok().unwrap(),
            x => writeln!(bw, "{x}").ok().unwrap(),
        }
    }
}
