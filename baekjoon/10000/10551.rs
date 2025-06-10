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
    fn raw(&mut self) -> &str {
        self.it.next().unwrap()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let mut keys = vec![vec![]; 8];
    keys[0] = vec!['1', 'Q', 'A', 'Z'];
    keys[1] = vec!['2', 'W', 'S', 'X'];
    keys[2] = vec!['3', 'E', 'D', 'C'];
    keys[3] = vec!['4', '5', 'R', 'T', 'F', 'G', 'V', 'B'];
    keys[4] = vec!['6', '7', 'Y', 'U', 'H', 'J', 'N', 'M'];
    keys[5] = vec!['8', 'I', 'K', ','];
    keys[6] = vec!['9', 'O', 'L', '.'];
    keys[7] = vec!['0', '-', '=', 'P', '[', ']', ';', '\'', '/'];
    let mut ans = [0; 8];
    for c in sc.raw().chars() {
        let i = keys.iter().position(|keys| keys.contains(&c)).unwrap();
        ans[i] += 1;
    }
    for x in ans {
        writeln!(bw, "{x}").ok();
    }
}
