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
    const SPECIES: [&str; 4] = ["Bobcat", "Coyote", "Mountain Lion", "Wolf"];
    let t = sc.read::<usize>();
    for _ in 0..t {
        let a = sc.read_bytes();
        let b = sc.read_bytes();
        let mut count = [0; 4];
        for c in b {
            match c {
                b'B' => count[0] += 2,
                b'C' => count[1] += 1,
                b'M' => count[2] += 4,
                _ => count[3] += 3,
            }
        }
        let (i, &mx) = count.iter().enumerate().max_by(|l, r| l.1.cmp(r.1)).unwrap();
        write!(bw, "{}: ", String::from_utf8(a).unwrap()).ok();
        if count.into_iter().filter(|&x| x == mx).count() == 1 {
            writeln!(bw, "The {} is the dominant species", SPECIES[i]).ok();
        } else {
            writeln!(bw, "There is no dominant species").ok();
        }
    }
}
