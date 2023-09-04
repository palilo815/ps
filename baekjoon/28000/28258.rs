fn ask(r: usize, c: usize) -> bool {
    println!("? {r} {c}");
    let mut s = String::new();
    std::io::stdin().read_line(&mut s).unwrap();
    s.starts_with('1')
}

fn main() {
    let (r1, c1) = (|| {
        for r in 0..10 {
            for c in 0..10 {
                if (r, c) != (0, 0) && (r, c) != (9, 9) && (r ^ c) & 1 == 0 && ask(r, c) {
                    return (r, c);
                }
            }
        }
        if ask(0, 0) {
            (0, 0)
        } else {
            (9, 9)
        }
    })();
    let mut second = vec![];
    if r1 != 0 {
        second.push((r1 - 1, c1));
    }
    if c1 != 0 {
        second.push((r1, c1 - 1));
    }
    if r1 != 9 {
        second.push((r1 + 1, c1));
    }
    if c1 != 9 {
        second.push((r1, c1 + 1));
    }
    let (r2, c2) = (|| {
        for &(r, c) in second.iter().skip(1) {
            if ask(r, c) {
                return (r, c);
            }
        }
        second[0]
    })();
    println!("! {r1} {c1} {r2} {c2}");
}
