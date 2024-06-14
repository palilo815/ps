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
    fn raw(&mut self) -> &str {
        self.it.next().unwrap()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let s = sc.raw();
    let n = s.len();
    let mut pref = vec![[0; 3]; 2 * n];
    for (i, c) in (1..pref.len()).zip(s.bytes().cycle()) {
        pref[i] = pref[i - 1];
        pref[i][(c - b'A') as usize] += 1;
    }
    let a = pref[n][0] as usize;
    let b = pref[n][1] as usize;
    let c = pref[n][2] as usize;
    let diff = |l: [i32; 3], r: [i32; 3]| -> [i32; 3] { [r[0] - l[0], r[1] - l[1], r[2] - l[2]] };
    let count = |mat: [[i32; 3]; 3]| -> i32 {
        let swap_ab = mat[0][1].min(mat[1][0]);
        let swap_bc = mat[1][2].min(mat[2][1]);
        let swap_ca = mat[2][0].min(mat[0][2]);
        swap_ab - swap_bc - swap_ca + 2 * (mat[2][1] + mat[2][0])
    };
    let mut mat = [[0; 3]; 3];
    let mut ans = i32::MAX;
    for i in 0..n {
        // case ABC
        mat[0] = diff(pref[i], pref[i + a]);
        mat[1] = diff(pref[i + a], pref[i + a + b]);
        mat[2] = diff(pref[i + a + b], pref[i + a + b + c]);
        ans = ans.min(count(mat));
        // case ACB
        mat[0] = diff(pref[i], pref[i + a]);
        mat[2] = diff(pref[i + a], pref[i + a + c]);
        mat[1] = diff(pref[i + a + c], pref[i + a + c + b]);
        ans = ans.min(count(mat));
    }
    writeln!(bw, "{ans}").ok();
}
