use std::io::*;

struct Scanner {
    it: std::str::Split<'static, char>,
}

impl Scanner {
    fn new() -> Self {
        let mut s = String::new();
        stdin().read_to_string(&mut s).ok();
        Self { it: s.leak().split('\n') }
    }
    fn get(&mut self) -> &str {
        self.it.next().unwrap()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let mut masks = [0; 20];
    let t = sc.get().parse::<usize>().unwrap();
    for tc in 1..=t {
        let mut it = sc.get().split_ascii_whitespace();
        let m = it.next().unwrap().parse::<usize>().unwrap();
        let n = it.next().unwrap().parse::<usize>().unwrap();
        let masks = &mut masks[..n];
        masks.fill_with(|| {
            sc.get()
                .split_ascii_whitespace()
                .fold(0, |acc, x| acc | (1 << (m - x.parse::<usize>().unwrap())))
        });
        let mut ans = i32::MAX;
        for i in 1_i32..(1 << n) {
            if i.count_ones() < ans.count_ones() {
                let mask = (0..n).filter(|pos| (i >> pos) & 1 == 1).map(|i| masks[i]).fold(0, std::ops::BitOr::bitor);
                if mask == (1 << m) - 1 {
                    ans = i;
                }
            }
        }
        write!(bw, "Data Set {tc}:").ok();
        for i in 0..n {
            if ans >> i & 1 == 1 {
                write!(bw, " {}", (b'A' + i as u8) as char).ok();
            }
        }
        writeln!(bw).ok();
        writeln!(bw).ok();
    }
}
