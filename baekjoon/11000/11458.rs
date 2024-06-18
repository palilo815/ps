use std::io::*;

struct Scanner {
    it: std::str::SplitAsciiWhitespace<'static>,
}

impl Scanner {
    fn new() -> Self {
        let mut s = String::new();
        stdin().read_to_string(&mut s).ok();
        Self {
            it: s.leak().split_ascii_whitespace(),
        }
    }
    fn read_bytes(&mut self) -> Vec<u8> {
        self.it.next().unwrap().bytes().collect()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    loop {
        let mut s = sc.read_bytes();
        if s == b"END" {
            break;
        }
        let mut neg = s[0] == b'-';
        if neg {
            s.remove(0);
            if let Some(x) = s.iter_mut().rev().find(|x| **x != b'9') {
                *x += 1;
            } else {
                s.insert(0, b'1');
            }
        } else {
            match s.iter_mut().enumerate().rev().find(|x| *x.1 != b'9') {
                Some((0, x)) => {
                    neg = true;
                    *x += 1;
                }
                Some((i, x)) => {
                    *x += 1;
                    match s[..=i].iter_mut().enumerate().skip(1).rev().find(|x| *x.1 != b'9') {
                        Some((j, y)) => {
                            *y += 1;
                            let k = (0..j).rev().find(|x| s[*x] != b'0').unwrap();
                            s[k] -= 1;
                            let capa = s.iter().skip(k + 1).fold(0, |acc, x| acc + (x - b'0') as i32);
                            s.iter_mut().skip(k + 1).fold(capa, |capa, x| {
                                let value = capa.min(9);
                                *x = b'0' + value as u8;
                                capa - value
                            });
                            let non_zero = s.iter().position(|x| *x != b'0').unwrap();
                            s.drain(..non_zero);
                        }
                        None => neg = true,
                    }
                }
                None => {
                    neg = true;
                    s.insert(0, b'1');
                }
            }
        }
        if neg {
            write!(bw, "-").ok();
        }
        writeln!(bw, "{}", String::from_utf8(s).unwrap()).ok();
    }
}
