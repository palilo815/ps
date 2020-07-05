#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define x first
#define y second
using namespace std;
using p = pair<int, int>;

const int M = 3000;

struct line {
    p p1, p2;
} a[M];
int parent[M];

int _find(int u) {
    if (parent[u] < 0) return u;
    return parent[u] = _find(parent[u]);
}
void _union(int u, int v) {
    u = _find(u), v = _find(v);
    if (u ^ v) {
        if (parent[u] < parent[v]) swap(u, v);
        parent[v] += parent[u];
        parent[u] = v;
    }
}
int ccw(p& a, p& b, p& c) {
    int ret = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    return ret ? (ret > 0 ? 1 : -1) : 0;
}
bool cross(line& a, line& b) {
    int A = ccw(a.p1, a.p2, b.p1) * ccw(a.p1, a.p2, b.p2);
    int B = ccw(b.p1, b.p2, a.p1) * ccw(b.p1, b.p2, a.p2);
    if (A | B) return A <= 0 && B <= 0;
    return a.p1 <= b.p2 && b.p1 <= a.p2;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    loop(i, N) {
        cin >> a[i].p1.x >> a[i].p1.y >> a[i].p2.x >> a[i].p2.y;
        if (a[i].p1 > a[i].p2) swap(a[i].p1, a[i].p2);
    }

    memset(parent, -1, sizeof(int) * N);
    loop(i, N - 1) for (int j = i + 1; j < N; ++j)
        if (cross(a[i], a[j]))
            _union(i, j);

    int cnt = 0, ans = 0;
    loop(i, N) if (parent[i] < 0) {
        ++cnt;
        ans = min(ans, parent[i]);
    }
    cout << cnt << '\n' << -ans;
    return 0;
}