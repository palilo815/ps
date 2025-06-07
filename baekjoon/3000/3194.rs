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
    fn raw(&mut self) -> &str {
        self.it.next().unwrap()
    }
}

struct Match {
    team1: usize,
    team2: usize,
    score1: i32,
    score2: i32,
}

#[derive(Clone, Copy, Default)]
struct InitialResult {
    diff: i32,
    goal: i32,
    win: i32,
}

const N: usize = 100;

fn f(teams: &mut [usize], matches: &[Match], results: &[InitialResult]) {
    let mut score = [0; N];
    let mut check = [false; N];
    teams.iter().for_each(|&t| check[t] = true);
    for &Match { team1, team2, score1, score2 } in matches {
        if check[team1] && check[team2] {
            match score1.cmp(&score2) {
                std::cmp::Ordering::Greater => score[team1] += 3,
                std::cmp::Ordering::Less => score[team2] += 3,
                _ => {
                    score[team1] += 1;
                    score[team2] += 1;
                }
            }
        }
    }
    let s = score[teams[0]];
    if teams.iter().all(|&t| score[t] == s) {
        teams.sort_unstable_by(|&l, &r| {
            results[r]
                .diff
                .cmp(&results[l].diff)
                .then(results[r].goal.cmp(&results[l].goal))
                .then(results[r].win.cmp(&results[l].win))
                .then(l.cmp(&r))
        });
        return;
    }
    teams.sort_unstable_by(|&l, &r| score[r].cmp(&score[l]));
    let mut l = 0;
    let mut r = 0;
    while l != teams.len() {
        while r != teams.len() && score[teams[l]] == score[teams[r]] {
            r += 1;
        }
        if l + 1 != r {
            f(&mut teams[l..r], matches, results);
        }
        l = r;
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let matches = (0..m)
        .map(|_| {
            let team1 = sc.read::<usize>() - 1;
            let team2 = sc.read::<usize>() - 1;
            let score = sc.raw();
            let score1 = (score.as_bytes()[0] - b'0') as i32;
            let score2 = (score.as_bytes()[2] - b'0') as i32;
            Match { team1, team2, score1, score2 }
        })
        .collect::<Vec<_>>();
    let mut results = [InitialResult::default(); N];
    for &Match { team1, team2, score1, score2 } in matches.iter() {
        results[team1].diff += score1 - score2;
        results[team2].diff += score2 - score1;
        results[team1].goal += score1;
        results[team2].goal += score2;
        results[team1].win += (score1 > score2) as i32;
        results[team2].win += (score2 > score1) as i32;
    }
    let mut teams = (0..n).collect::<Vec<_>>();
    f(&mut teams, &matches, &results);
    for t in teams {
        write!(bw, "{} ", t + 1).ok();
    }
}
