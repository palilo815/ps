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
    fn read_bytes(&mut self) -> Vec<u8> {
        self.it.next().unwrap().bytes().collect()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let f = |books: &[u8]| -> (usize, usize, usize) {
        books.iter().fold((0, 0, 0), |(l, m, s), b| match *b {
            b'L' => (l + 1, m, s),
            b'M' => (l, m + 1, s),
            _ => (l, m, s + 1),
        })
    };
    let books = sc.read_bytes();
    let total = f(&books);
    let mut b0 = f(&books[..total.0]);
    let mut b1 = f(&books[total.0..total.0 + total.1]);
    let mut b2 = (total.0 - b0.0 - b1.0, total.1 - b0.1 - b1.1, total.2 - b0.2 - b1.2);
    let mut ans = 0;
    let swap = b0.1.min(b1.0);
    ans += swap;
    b0 = (b0.0 + swap, b0.1 - swap, b0.2);
    b1 = (b1.0 - swap, b1.1 + swap, b1.2);
    let swap = b1.2.min(b2.1);
    ans += swap;
    b2 = (b2.0, b2.1 - swap, b2.2 + swap);
    let swap = b2.0.min(b0.2);
    ans += swap;
    b0 = (b0.0 + swap, b0.1, b0.2 - swap);
    ans += 2 * (b0.1 + b0.2);
    writeln!(bw, "{ans}").ok();
}
