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
    fn read_array<const N: usize>(&mut self) -> [u8; N] {
        let s = self.it.next().unwrap();
        let mut a = [0; N];
        a[..s.len()].copy_from_slice(s.as_bytes());
        a
    }
    fn raw(&mut self) -> &str {
        self.it.next().unwrap()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    const N: usize = 5000;
    const PREF: [usize; 13] = [0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365];
    let parse = |date: [u8; 10], time: [u8; 5]| -> usize {
        let date: [usize; 10] = date.map(|x| (x - b'0') as usize);
        let y = date[3] - 3;
        let m = date[5] * 10 + date[6] - 1;
        let d = date[8] * 10 + date[9] - 1;
        let days = d + PREF[m] + if y == 3 && m > 1 { 1 } else { 0 } + 365 * y;
        let time: [usize; 5] = time.map(|x| (x - b'0') as usize);
        let h = time[0] * 10 + time[1];
        let m = time[3] * 10 + time[4];
        let minutes = m + h * 60;
        minutes + days * 60 * 24
    };
    let mut in_times = [0; N];
    let mut out_times = [0; N];
    let t = sc.read::<usize>();
    for _ in 0..t {
        let n = sc.read::<usize>();
        let c = sc.read::<usize>();
        let in_times = &mut in_times[..n];
        let out_times = &mut out_times[..n];
        for (it, ot) in in_times.iter_mut().zip(out_times.iter_mut()) {
            sc.raw();
            let date = sc.read_array();
            let time = sc.read_array();
            *it = parse(date, time);
            let date = sc.read_array();
            let time = sc.read_array();
            *ot = parse(date, time) + c;
        }
        in_times.sort_unstable();
        out_times.sort_unstable();
        let mut ans = 0;
        let mut acc = 0;
        let mut i = 0;
        let mut j = 0;
        while i != n {
            if in_times[i] < out_times[j] {
                i += 1;
                acc += 1;
                ans = ans.max(acc);
            } else {
                j += 1;
                acc -= 1;
            }
        }
        writeln!(bw, "{ans}").ok();
    }
}
