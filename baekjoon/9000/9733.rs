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
    fn next(&mut self) -> Option<&str> {
        self.it.next()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    const TASK: [&str; 7] = ["Re", "Pt", "Cc", "Ea", "Tb", "Cm", "Ex"];
    let mut count = [0; 7];
    let mut total = 0;
    while let Some(s) = sc.next() {
        if let Some(i) = TASK.iter().position(|&x| x == s) {
            count[i] += 1;
        }
        total += 1;
    }
    for (task, count) in TASK.into_iter().zip(count.into_iter()) {
        let frac = count as f64 / total as f64;
        writeln!(bw, "{task} {count} {frac:.2}").ok();
    }
    writeln!(bw, "Total {total} 1.00").ok();
}
