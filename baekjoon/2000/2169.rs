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
    const NEG: i32 = !0x3f3f3f3f;
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let mut cur = vec![0; m];
    let mut prv = vec![NEG; m];
    prv[0] = 0;
    let mut val = vec![0; m];
    for _ in 0..n {
        cur.fill(NEG);
        val.fill_with(|| sc.read::<i32>());
        let mut to_right = NEG;
        for i in 0..m {
            to_right = to_right.max(prv[i]) + val[i];
            cur[i] = to_right;
        }
        let mut to_left = NEG;
        for i in (0..m).rev() {
            to_left = to_left.max(prv[i]) + val[i];
            cur[i] = cur[i].max(to_left);
        }
        std::mem::swap(&mut prv, &mut cur);
    }
    writeln!(bw, "{}", prv[m - 1]).ok();
}
