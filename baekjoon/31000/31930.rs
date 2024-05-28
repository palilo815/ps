fn read() -> String {
    let mut s = String::new();
    std::io::stdin().read_line(&mut s).unwrap();
    s.trim_end().into()
}

fn ask(l: usize, r: usize) -> bool {
    println!("AK {l} {r}");
    read() == "O"
}

fn gotcha(ans: (usize, usize)) {
    println!("! {} {}", ans.0, ans.1);
}

fn binary_search(mut l: usize, mut r: usize) -> usize {
    let base = l;
    while l != r {
        // first true
        let m = l + (r - l) / 2;
        if ask(base, m) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    l
}

fn window_search(n: usize) -> (usize, usize) {
    let len = n / 2 - 1;
    let i = (2..).find(|&i| ask(i, i + len)).unwrap();
    if ask(i - 1, i - 1) {
        (i - 1, binary_search(i, n / 2))
    } else {
        (i + len, binary_search(i + len + 1, n))
    }
}

fn main() {
    let t = read().parse::<usize>().unwrap();
    for _ in 0..t {
        let n = read().parse::<usize>().unwrap();
        let ans = if ask(1, n / 2) {
            (binary_search(1, n / 2), binary_search(n / 2 + 1, n))
        } else {
            window_search(n)
        };
        gotcha(ans);
    }
}
