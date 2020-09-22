#include <bits/stdc++.h>
#define loop(i, n) for (int i = 0; i < n; ++i)
using namespace std;
struct elem {
    int d, i, j;
    elem(int d, int i, int j) : d(d), i(i), j(j) {}
    bool operator<(const elem& rhs) const {
        return d > rhs.d;
    }
};

const int mxN = 5e5;

int x[mxN], l[mxN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, M;
    cin >> N >> M;
    if ((long long)N * (N - 1) / 2 < M) {
        cout << "no";
        return 0;
    }

    loop(i, N) cin >> x[i];
    loop(i, M) cin >> l[i];
    sort(l, l + M);

    priority_queue<elem> pq;
    for (int i = 0; i < N - 1; ++i)
        pq.emplace(x[i + 1] - x[i], i, i + 1);

    for (int k = 0; k < M; ++k) {
        auto [d, i, j] = pq.top();
        pq.pop();

        if (l[k] < d) {
            cout << "no";
            return 0;
        }
        if (i) pq.emplace(x[j] - x[i - 1], i - 1, j);
    }
    cout << "yes";
    return 0;
}