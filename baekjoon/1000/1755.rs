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
    const ORDER: [u32; 10] = [9, 4, 8, 7, 2, 1, 6, 5, 0, 3];
    let l = sc.read::<usize>();
    let r = sc.read::<usize>();
    let mut a = (l..=r).collect::<Vec<_>>();
    a.sort_unstable_by(|&l, &r| {
        let l1 = if l > 9 { l / 10 } else { l };
        let r1 = if r > 9 { r / 10 } else { r };
        ORDER[l1].cmp(&ORDER[r1]).then({
            if l > 9 && r > 9 {
                ORDER[l % 10].cmp(&ORDER[r % 10])
            } else {
                l.cmp(&r)
            }
        })
    });
    for chunk in a.chunks(10) {
        for x in chunk {
            write!(bw, "{x} ").ok();
        }
        writeln!(bw).ok();
    }
}
