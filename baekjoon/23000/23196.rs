use std::io::*;

struct Scanner<'a> {
    it: std::str::SplitWhitespace<'a>,
}

impl<'a> Scanner<'a> {
    fn new(s: &'a str) -> Scanner<'a> {
        Scanner {
            it: s.split_whitespace(),
        }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let k = sc.read::<usize>();
    let mut pref = vec![0; n + 1];
    let mut delta = vec![0; n + 1];
    for _ in 0..k {
        let c = sc.read::<char>();
        let l = sc.read::<usize>() - 1;
        let r = sc.read::<usize>();
        match c {
            'R' => {
                pref[l] += 1;
                pref[r] -= 1;
            }
            'D' => {
                pref[l] -= 1;
                pref[r] += 1;
            }
            'H' => {
                pref[l] += 1;
                pref[r] -= 1;
                if r - l > 2 {
                    let m = l + (r - l) / 2;
                    delta[l] += 1;
                    delta[r - 1] += 1;
                    if (r - l) & 1 == 0 {
                        delta[m - 1] -= 1;
                        delta[m] -= 1;
                    } else {
                        delta[m] -= 2;
                    }
                }
            }
            _ => {
                pref[l] -= 1;
                pref[r] += 1;
                if r - l > 2 {
                    let m = l + (r - l) / 2;
                    delta[l] -= 1;
                    delta[r - 1] -= 1;
                    if (r - l) & 1 == 0 {
                        delta[m - 1] += 1;
                        delta[m] += 1;
                    } else {
                        delta[m] += 2;
                    }
                }
            }
        }
    }
    let mut d = 0;
    for i in 0..n {
        pref[i] += d as i64;
        pref[i + 1] += pref[i];
        d += delta[i];
    }
    for x in pref.into_iter().take(n) {
        writeln!(out, "{x}").ok();
    }
}
