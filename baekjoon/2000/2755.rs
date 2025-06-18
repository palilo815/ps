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
    const A: [i32; 6] = [400, 300, 200, 100, i32::MIN, 0];
    let n = sc.read::<usize>();
    let mut a = 0;
    let mut b = 0;
    for _ in 0..n {
        let _ = sc.raw();
        let credit = sc.read::<i32>();
        let grade = sc.raw().as_bytes();
        let grade = A[(grade[0] - b'A') as usize]
            + match grade.get(1) {
                Some(b'+') => 30,
                Some(b'-') => -30,
                _ => 0,
            };
        a += grade * credit;
        b += credit;
    }
    let c = a / b;
    writeln!(bw, "{}.{:02}", c / 100, c % 100 + (a % b * 2 >= b) as i32).ok();
}
