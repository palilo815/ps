const MOD: u32 = 998_244_353;

trait Modulo {
    fn mod_add(&self, x: Self) -> Self;
    fn mod_sub(&self, x: Self) -> Self;
    fn mod_mul(&self, x: Self) -> Self;
    fn mod_div(&self, x: Self) -> Self;
    fn mod_pow(&self, p: u64) -> Self;
    fn mod_inv(&self) -> Self;
}

impl Modulo for u32 {
    fn mod_add(&self, x: Self) -> Self {
        let (r, f) = self.wrapping_add(x).overflowing_sub(MOD);
        if f {
            self.wrapping_add(x)
        } else {
            r
        }
    }
    fn mod_sub(&self, x: Self) -> Self {
        let (r, f) = self.overflowing_sub(x);
        if f {
            r.wrapping_add(MOD)
        } else {
            r
        }
    }
    fn mod_mul(&self, x: Self) -> Self {
        (*self as u64 * x as u64 % MOD as u64) as u32
    }
    fn mod_div(&self, x: Self) -> Self {
        self.mod_mul(x.mod_inv())
    }
    fn mod_pow(&self, mut p: u64) -> Self {
        let mut x = *self;
        let mut r = 1;
        while p != 0 {
            if p & 1 == 1 {
                r = r.mod_mul(x);
            }
            x = x.mod_mul(x);
            p >>= 1;
        }
        r
    }
    fn mod_inv(&self) -> Self {
        self.mod_pow(MOD as u64 - 2)
    }
}
