/**
* @source   https://codeforces.com/blog/entry/17023
* @date     2022-01-23
* @author   palilo
* @brief    fast Kuhn's algorithm
*           better than heuristic version (https://cp-algorithms.com/graph/kuhn_maximum_bipartite_matching.html#improved-implementation)
*           actual run-time is much faster than theoretical time complexity
* @usage    n <- # of vertices in left group
*           m <- # of vertices in right group
*           `matching` returns the matched pairs of the left group (usize::MAX if not matched)
* @time     O(n^2 m) 
*           ^^^^^^^^ place small group to left
* @todo     RIIR `minimum_vertex_cover` (https://github.com/palilo815/Team-Library/blob/main/graph/bipartite_matching.cpp)
*                 ^^^^^^^^^^^^^^^^^^^^ this appears very rarely.
* @test     https://judge.yosupo.jp/submission/75537
*/
struct BipartiteMatching {
    n: usize,
    m: usize,
    adj: Vec<Vec<usize>>,
}

impl BipartiteMatching {
    fn new(n: usize, m: usize) -> Self {
        Self {
            n,
            m,
            adj: vec![vec![]; n],
        }
    }
    fn add_edge(&mut self, u: usize, v: usize) {
        assert!(u < self.n && v < self.m);
        self.adj[u].push(v);
    }
    fn matching(&self) -> Vec<usize> {
        let mut visited = vec![false; self.n];
        let mut mat = vec![usize::MAX; self.n];
        let mut rmat = vec![usize::MAX; self.m];
        let mut update = true;
        while update {
            visited.fill(false);
            update = false;
            for u in 0..self.n {
                update |= mat[u] == usize::MAX && self.dfs(&mut visited, &mut mat, &mut rmat, u);
            }
        }
        mat
    }
    fn dfs(&self, visited: &mut [bool], mat: &mut [usize], rmat: &mut [usize], u: usize) -> bool {
        visited[u] = true;
        for &v in self.adj[u].iter() {
            if rmat[v] == usize::MAX || (!visited[rmat[v]] && self.dfs(visited, mat, rmat, rmat[v]))
            {
                mat[u] = v;
                rmat[v] = u;
                return true;
            }
        }
        false
    }
}
