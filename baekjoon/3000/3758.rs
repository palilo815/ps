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
    const N: usize = 100;
    let mut score = [[0; N]; N];
    let mut submit = [0; N];
    let mut last = [0; N];
    let t = sc.read::<usize>();
    for _ in 0..t {
        let n = sc.read::<usize>();
        let k = sc.read::<usize>();
        let t = sc.read::<usize>() - 1;
        let m = sc.read::<usize>();
        let score = &mut score[..n];
        let submit = &mut submit[..n];
        let last = &mut last[..n];
        score.fill([0; N]);
        submit.fill(0);
        last.fill(0);
        for time in 1..=m {
            let i = sc.read::<usize>() - 1;
            let j = sc.read::<usize>() - 1;
            let s = sc.read::<u32>();
            score[i][j] = score[i][j].max(s);
            submit[i] += 1;
            last[i] = time << 1;
        }
        for score in score.iter_mut() {
            score[0] = score.iter().take(k).sum::<u32>();
        }
        last[t] -= 1;
        let mut ord = (0..n).collect::<Vec<_>>();
        ord.sort_unstable_by(|&l, &r| {
            score[r][0].cmp(&score[l][0]).then(submit[l].cmp(&submit[r])).then(last[l].cmp(&last[r]))
        });
        let ans = ord.into_iter().position(|i| i == t).unwrap() + 1;
        writeln!(bw, "{ans}").ok();
    }
}
