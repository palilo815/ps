pub struct DisjointSet {
    p: Vec<i32>,
}

impl DisjointSet {
    pub fn new(n: usize) -> DisjointSet {
        DisjointSet { p: vec![-1; n] }
    }
    pub fn find(&mut self, mut u: usize) -> usize {
        assert!(u < self.p.len());
        while self.p[u] >= 0 {
            if self.p[self.p[u] as usize] >= 0 {
                self.p[u] = self.p[self.p[u] as usize];
            }
            u = self.p[u] as usize;
        }
        u
    }
    pub fn unite(&mut self, u: usize, v: usize) -> bool {
        assert!(u < self.p.len() && v < self.p.len());
        let mut u = self.find(u);
        let mut v = self.find(v);
        if u == v {
            return false;
        }
        if self.p[u] > self.p[v] {
            std::mem::swap(&mut u, &mut v);
        }
        self.p[u] += self.p[v];
        self.p[v] = u as i32;
        true
    }
    pub fn size(&mut self, u: usize) -> usize {
        assert!(u < self.p.len());
        let root = self.find(u);
        (-self.p[root]) as usize
    }
}
