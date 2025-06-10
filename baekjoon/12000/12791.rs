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
}

struct Album<'a> {
    y: i32,
    s: &'a str,
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    const A: [Album; 25] = [
        Album { y: 1967, s: "DavidBowie" },
        Album { y: 1969, s: "SpaceOddity" },
        Album { y: 1970, s: "TheManWhoSoldTheWorld" },
        Album { y: 1971, s: "HunkyDory" },
        Album {
            y: 1972,
            s: "TheRiseAndFallOfZiggyStardustAndTheSpidersFromMars",
        },
        Album { y: 1973, s: "AladdinSane" },
        Album { y: 1973, s: "PinUps" },
        Album { y: 1974, s: "DiamondDogs" },
        Album { y: 1975, s: "YoungAmericans" },
        Album { y: 1976, s: "StationToStation" },
        Album { y: 1977, s: "Low" },
        Album { y: 1977, s: "Heroes" },
        Album { y: 1979, s: "Lodger" },
        Album { y: 1980, s: "ScaryMonstersAndSuperCreeps" },
        Album { y: 1983, s: "LetsDance" },
        Album { y: 1984, s: "Tonight" },
        Album { y: 1987, s: "NeverLetMeDown" },
        Album { y: 1993, s: "BlackTieWhiteNoise" },
        Album { y: 1995, s: "1.Outside" },
        Album { y: 1997, s: "Earthling" },
        Album { y: 1999, s: "Hours" },
        Album { y: 2002, s: "Heathen" },
        Album { y: 2003, s: "Reality" },
        Album { y: 2013, s: "TheNextDay" },
        Album { y: 2016, s: "BlackStar" },
    ];
    let n = sc.read::<usize>();
    for _ in 0..n {
        let y1 = sc.read::<i32>();
        let y2 = sc.read::<i32>();
        let lo = A.partition_point(|x| x.y < y1);
        let up = A.partition_point(|x| x.y <= y2);
        writeln!(bw, "{}", up - lo).ok();
        for album in A.iter().take(up).skip(lo) {
            writeln!(bw, "{} {}", album.y, album.s).ok();
        }
    }
}
