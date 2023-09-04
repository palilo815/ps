fn read() -> u32 {
    let mut s = String::new();
    std::io::stdin().read_line(&mut s).unwrap();
    s.trim().parse::<u32>().unwrap()
}

fn ask(x: u32) -> u32 {
    println!("? {}", x);
    read()
}

fn gotcha(x: u32) {
    println!("! {}", x);
}

fn main() {
    let n = read();
    let mut lo = 2;
    let mut hi = n - 1;
    while lo != hi {
        let mid = lo + (hi - lo) / 2;
        if ask(mid) * 2 > mid {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    gotcha(lo);
}
