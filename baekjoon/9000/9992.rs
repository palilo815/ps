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

fn f<'a>(s: &'a [u8], dp: &mut std::collections::HashMap<&'a [u8], i32>) -> i32 {
    if let Some(x) = dp.get(s) {
        return *x;
    }
    let mut res = 1;
    for i in 1..s.len().div_ceil(2) {
        let (front, word) = s.split_at(i);
        if front == &word[..i] {
            res += f(word, dp);
        }
        if front == &word[word.len() - i..] {
            res += f(word, dp);
        }
        let (word, back) = s.split_at(s.len() - i);
        if &word[..i] == back {
            res += f(word, dp);
        }
        if &word[word.len() - i..] == back {
            res += f(word, dp);
        }
    }
    res %= 2014;
    dp.insert(s, res);
    res
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let s = sc.raw().as_bytes();
    let mut dp = std::collections::HashMap::new();
    let ans = f(s, &mut dp);
    writeln!(bw, "{}", if ans == 0 { 2013 } else { ans - 1 }).ok();
}
