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
    const N: usize = 318_137;
    let mut prime = vec![true; N + 1];
    prime[0] = false;
    prime[1] = false;
    for i in 2.. {
        if i * i > N {
            break;
        }
        if prime[i] {
            for j in (i * i..=N).step_by(i) {
                prime[j] = false;
            }
        }
    }
    let mut sup = Vec::with_capacity(3000);
    let mut cnt = 0;
    for (i, &p) in prime.iter().enumerate() {
        if p {
            cnt += 1;
            if prime[cnt] {
                sup.push(i);
            }
        }
    }
    let t = sc.read::<usize>();
    for _ in 0..t {
        writeln!(out, "{}", sup[sc.read::<usize>() - 1]).ok();
    }
}
