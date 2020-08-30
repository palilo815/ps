#include <bits/stdc++.h>
using namespace std;
using ui = unsigned;
struct beer {
    ui like, deg;
};

const ui mxN = 2e5;

beer a[mxN];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    ui N, M, K; cin >> N >> M >> K;
    for (ui i = 0; i < K; ++i)
        cin >> a[i].like >> a[i].deg;

    sort(a, a + K, [&](auto & a, auto & b) {
        return a.deg < b.deg;
    });

    priority_queue<ui, vector<ui>, greater<ui>> pq;
    ui sum = 0;
    for (ui i = 0; i < N; ++i) {
        sum += a[i].like;
        pq.emplace(a[i].like);
    }

    for (ui i = N;; ++i) {
        if (sum >= M) {cout << a[i - 1].deg; return 0;}
        if (i == K) break;
        pq.emplace(a[i].like);
        sum += a[i].like - pq.top();
        pq.pop();
    }
    cout << -1;
    return 0;
}