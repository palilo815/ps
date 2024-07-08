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
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
    fn raw(&mut self) -> &str {
        self.it.next().unwrap()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let mut face = [[' '; 9]; 6];
    loop {
        if sc.raw() == "ENDOFINPUT" {
            break;
        }
        face[0].iter_mut().for_each(|x| *x = sc.read());
        for i in (0..9).step_by(3) {
            for f in face[1..5].iter_mut() {
                f.iter_mut().skip(i).take(3).for_each(|x| *x = sc.read());
            }
        }
        face[5].iter_mut().for_each(|x| *x = sc.read());
        loop {
            let (fid, sides) = match sc.raw() {
                "top" => (0, [(2, (0, 1, 2)), (3, (0, 1, 2)), (4, (0, 1, 2)), (1, (0, 1, 2))]),
                "left" => (1, [(5, (6, 3, 0)), (2, (6, 3, 0)), (0, (6, 3, 0)), (4, (2, 5, 8))]),
                "front" => (2, [(5, (0, 1, 2)), (3, (6, 3, 0)), (0, (8, 7, 6)), (1, (2, 5, 8))]),
                "right" => (3, [(5, (2, 5, 8)), (4, (6, 3, 0)), (0, (2, 5, 8)), (2, (2, 5, 8))]),
                "back" => (4, [(5, (8, 7, 6)), (1, (6, 3, 0)), (0, (0, 1, 2)), (3, (2, 5, 8))]),
                "bottom" => (5, [(4, (8, 7, 6)), (3, (8, 7, 6)), (2, (8, 7, 6)), (1, (8, 7, 6))]),
                "END" => break,
                _ => unreachable!(),
            };
            let dir = match sc.raw() {
                "left" => false,
                "right" => true,
                _ => unreachable!(),
            };
            let f = face[fid];
            if dir {
                face[fid] = [
                    f[6], f[3], f[0], //
                    f[7], f[4], f[1], //
                    f[8], f[5], f[2], //
                ];
                let tmp = face[sides[0].0];
                for i in 0..3 {
                    let (sid1, x1) = sides[i];
                    let (sid2, x2) = sides[i + 1];
                    face[sid1][x1.0] = face[sid2][x2.0];
                    face[sid1][x1.1] = face[sid2][x2.1];
                    face[sid1][x1.2] = face[sid2][x2.2];
                }
                let (sid1, x1) = sides[3];
                face[sid1][x1.0] = tmp[sides[0].1 .0];
                face[sid1][x1.1] = tmp[sides[0].1 .1];
                face[sid1][x1.2] = tmp[sides[0].1 .2];
            } else {
                face[fid] = [
                    f[2], f[5], f[8], //
                    f[1], f[4], f[7], //
                    f[0], f[3], f[6], //
                ];
                let tmp = face[sides[3].0];
                for i in (0..3).rev() {
                    let (sid1, x1) = sides[i + 1];
                    let (sid2, x2) = sides[i];
                    face[sid1][x1.0] = face[sid2][x2.0];
                    face[sid1][x1.1] = face[sid2][x2.1];
                    face[sid1][x1.2] = face[sid2][x2.2];
                }
                let (sid1, x1) = sides[0];
                face[sid1][x1.0] = tmp[sides[3].1 .0];
                face[sid1][x1.1] = tmp[sides[3].1 .1];
                face[sid1][x1.2] = tmp[sides[3].1 .2];
            }
        }
        let ans = face.iter().all(|f| f.iter().all(|&c| c == f[0]));
        writeln!(bw, "{}", if ans { "Yes" } else { "No" }).ok();
    }
}
