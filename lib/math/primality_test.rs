mod primality_test {
    pub fn is_prime(n: T) -> bool {
        if n < 2 {
            return false;
        } else if n < 4 {
            return true;
        } else if n % 6 != 1 && n % 6 != 5 {
            return false;
        }
        let s = (n - 1).trailing_zeros();
        let d = n >> s;
        if n < 4759123141 {
            BASE_SMALL.iter()
        } else {
            BASE_LARGE.iter()
        }
        .take_while(|&&x| x < n)
        .all(|&b| !check_composite(n, b, d, s))
    }
    pub fn factorize(n: T) -> Vec<T> {
        if n == 1 {
            return vec![];
        } else if is_prime(n) {
            return vec![n];
        }
        // TODO
        unreachable!();
        vec![]
    }

    type T = u64;

    const BASE_SMALL: [T; 3] = [2, 7, 61];
    const BASE_LARGE: [T; 7] = [2, 325, 9375, 28178, 450775, 9780504, 1795265022];

    fn check_composite(n: T, x: T, d: T, s: u32) -> bool {
        let n = n as u128;
        let mut x = pow_mod(x as u128, d, n);
        if x == 1 || x == n - 1 {
            return false;
        }
        for _ in 1..s {
            x = x * x % n;
            if x == n - 1 {
                return false;
            }
        }
        true
    }
    fn pow_mod(mut a: u128, mut p: T, m: u128) -> u128 {
        let mut r = 1;
        while p != 0 {
            if p & 1 == 1 {
                r = r * a % m;
            }
            a = a * a % m;
            p >>= 1;
        }
        r
    }
}
