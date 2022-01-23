/**
* @date     2022-01-21
* @author   palilo
* @brief    disjoint-set-union (a.k.a. union-find)
*/
pub struct DisjointSet {
    p: Vec<i32>,
}

impl DisjointSet {
    pub fn new(n: usize) -> Self {
        Self { p: vec![-1; n] }
    }
    pub fn find(&mut self, u: usize) -> usize {
        if self.p[u] < 0 {
            u
        } else {
            let rt = self.find(self.p[u] as usize);
            self.p[u] = rt as i32;
            rt
        }
    }
    pub fn unite(&mut self, u: usize, v: usize) -> bool {
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
    pub fn same(&mut self, u: usize, v: usize) -> bool {
        self.find(u) == self.find(v)
    }
    pub fn size_of(&mut self, u: usize) -> usize {
        let root = self.find(u);
        (-self.p[root]) as usize
    }
    pub fn num_components(&self) -> usize {
        self.p.iter().filter(|x| x.is_negative()).count()
    }
}