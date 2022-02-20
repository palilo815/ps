/**
* @source   https://prng.di.unimi.it/xoroshiro128plus.c
* @date     2022-02-20
* @author   David Blackman and Sebastiano Vigna (vigna@acm.org)
* @brief    xoroshiro128+ algorithm 1.0
*/
struct Random {
    s: [usize; 2],
}

impl Random {
    fn new() -> Self {
        let x = Box::into_raw(Box::new("palilo")) as usize;
        Self {
            s: [x, x.rotate_left(32)],
        }
    }
    fn next(&mut self) -> usize {
        let s0 = self.s[0];
        let mut s1 = self.s[1];
        let result = s0.wrapping_add(s1);
        s1 ^= s0;
        self.s[0] = s0.rotate_left(24) ^ s1 ^ (s1 << 16);
        self.s[1] = s1.rotate_left(37);
        result
    }
}
