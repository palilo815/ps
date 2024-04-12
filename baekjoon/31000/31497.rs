fn read() -> String {
    let mut s = String::new();
    std::io::stdin().read_line(&mut s).unwrap();
    s.trim().into()
}

fn ask(x: &String) -> bool {
    println!("? {}", x);
    read().starts_with('1')
}

fn gotcha(x: &String) {
    println!("! {}", x);
}

fn main() {
    let n = read().trim().parse::<usize>().unwrap();
    let names = (0..n).map(|_| read()).collect::<Vec<_>>();
    for name in names {
        if ask(&name) || ask(&name) {
            gotcha(&name);
            return;
        }
    }
}
