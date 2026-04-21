use std::io::*;

struct Scanner {
    it: std::str::SplitAsciiWhitespace<'static>,
}

impl Scanner {
    fn new() -> Self {
        let mut buf = Vec::new();
        stdin().lock().read_to_end(&mut buf).ok();
        let s = unsafe { std::str::from_utf8_unchecked(Box::leak(buf.into_boxed_slice())) };
        Self { it: s.split_ascii_whitespace() }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let l = sc.read::<usize>();
    let k = sc.read::<usize>();
    let mut pref = vec![0; l + 1];
    for _ in 0..k {
        pref[sc.read::<usize>()] += 1;
    }
    for i in 0..l {
        pref[i + 1] += pref[i];
    }
    let mut acc = 0;
    let mut fps = 1;
    for s in 1.. {
        let quo = fps / l;
        let rem = fps % l;
        let i = acc % l;
        acc += fps;
        fps += quo * k
            + if i + rem > l {
                pref[l] - pref[i] + pref[i + rem - l]
            } else {
                pref[i + rem] - pref[i]
            };
        if acc >= n * l {
            writeln!(bw, "{s}").ok();
            break;
        }
    }
}
