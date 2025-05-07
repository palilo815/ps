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
    let mut visited = vec![vec![false; m]; n];
    let mut cur = vec![(0, 0)];
    let mut prv = vec![];
    let mut check = [false; 26];
    check[(grid[0][0] - b'a') as usize] = true;
    let mut ans = vec![0; n + m - 1];
    ans.fill_with(|| {
        let min = check.iter().position(|&x| x).unwrap() as u8 + b'a';
        check.fill(false);
        cur.retain(|&(x, y)| grid[x][y] == min);
        std::mem::swap(&mut cur, &mut prv);
        cur.clear();
        for &(x, y) in prv.iter() {
            if x + 1 != n && !visited[x + 1][y] {
                visited[x + 1][y] = true;
                check[(grid[x + 1][y] - b'a') as usize] = true;
                cur.push((x + 1, y));
            }
            if y + 1 != m && !visited[x][y + 1] {
                visited[x][y + 1] = true;
                check[(grid[x][y + 1] - b'a') as usize] = true;
                cur.push((x, y + 1));
            }
        }
        min
    });
    writeln!(bw, "{}", String::from_utf8(ans).unwrap()).ok();
}
