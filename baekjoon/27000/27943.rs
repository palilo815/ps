fn read() -> String {
    let mut s = String::new();
    std::io::stdin().read_line(&mut s).unwrap();
    s
}

fn ask(x: usize) -> String {
    println!("? {}", x);
    read()
}

fn main() {
    let n = read().trim().parse::<usize>().unwrap();
    let k = ask((n + 1) / 2);
    let f = |mid| -> bool { ask(mid) == k };
    let l = {
        let mut lo = 1;
        let mut hi = (n + 1) / 2;
        while lo != hi {
            let mid = lo + (hi - lo) / 2;
            if f(mid) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        lo
    };
    let r = {
        let mut lo = (n + 1) / 2;
        let mut hi = n;
        while lo != hi {
            let mid = hi - (hi - lo) / 2;
            if f(mid) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }
        lo
    };
    println!("! {l} {r}");
}
