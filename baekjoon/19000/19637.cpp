#include <bits/stdc++.h>
using namespace std;
struct elem {
    char s[12];
    int x;
};

const int mxN = 1e5;

elem a[mxN];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M; cin >> N >> M;
    for (int i = 0; i < N; ++i)
        cin >> a[i].s >> a[i].x;

    stable_sort(a, a + N, [&](auto & a, auto & b) {
        return a.x < b.x;
    });
    N = unique(a, a + N, [&](auto & a, auto & b) {
        return a.x == b.x;
    }) - a;

    for (elem e; M--;) {
        cin >> e.x;
        cout << lower_bound(a, a + N, e, [&](auto & a, auto & b) {
            return a.x < b.x;
        })->s << '\n';
    }
    return 0;
}