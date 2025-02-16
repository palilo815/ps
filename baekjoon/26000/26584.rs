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
    const LIM: [u64; 4] = [0, 365, 24, 60];
    const UNIT: [&str; 4] = [" year(s)", " day(s)", " hour(s)", " minute(s)"];
    let t = sc.get().parse::<usize>().unwrap();
    for _ in 0..t {
        let mut time = [0; 4];
        let mut it = sc.get().split(',');
        let game = it.next().unwrap();
        time[3] = it.next().unwrap().parse::<u64>().unwrap();
        for i in (1..4).rev() {
            time[i - 1] = time[i] / LIM[i];
            time[i] %= LIM[i];
        }
        write!(bw, "{game} -").ok();
        (0..4).filter(|&i| time[i] != 0).for_each(|i| {
            write!(bw, " {}{}", time[i], UNIT[i]).ok();
        });
        writeln!(bw).ok();
    }
}
