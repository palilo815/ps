use std::io::*;

struct Scanner<'a> {
    it: std::str::SplitWhitespace<'a>,
}

impl<'a> Scanner<'a> {
    fn new(s: &str) -> Scanner {
        Scanner {
            it: s.split_whitespace(),
        }
    }
    fn read_bytes(&mut self) -> Vec<u8> {
        self.it.next().unwrap().bytes().collect()
    }
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let mut offset = [0; 26];
    offset[0] = 1;
    for i in 1..26 {
        offset[i] = offset[i - 1] * 1511_usize;
    }
    let s = sc.read_bytes();
    let t = sc.read_bytes();
    let mut set = std::collections::HashSet::new();
    for len in (1..=s.len().min(t.len())).rev() {
        let mut h = s.iter().take(len).fold(0, |acc, &x| acc + offset[(x - b'a') as usize]);
        set.clear();
        set.insert(h);
        for i in len..s.len() {
            h += offset[(s[i] - b'a') as usize] - offset[(s[i - len] - b'a') as usize];
            set.insert(h);
        }
        h = t.iter().take(len).fold(0, |acc, &x| acc + offset[(x - b'a') as usize]);
        if set.contains(&h)
            || (len..t.len()).any(|i| {
                h += offset[(t[i] - b'a') as usize] - offset[(t[i - len] - b'a') as usize];
                set.contains(&h)
            })
        {
            writeln!(out, "{len}").ok();
            return;
        }
    }
    writeln!(out, "0").ok();
}
