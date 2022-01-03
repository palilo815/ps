fn main() {
    use std::io::Write;
    let out = std::io::stdout();
    let mut out = std::io::BufWriter::new(out.lock());
    let mut has_parent = [false; 10001];
    for mut x in 1..=10000 {
        let mut sum = x;
        while x != 0 {
            sum += x % 10;
            x /= 10;
        }
        if sum <= 10000 {
            has_parent[sum] = true;
        }
    }
    has_parent[0] = true;
    for (i, &x) in has_parent.iter().enumerate() {
        if !x {
            writeln!(out, "{}", i).ok();
        }
    }
}
