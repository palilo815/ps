#include <bits/stdc++.h>
using namespace std;

const int max_N = 1000;
const int max_K = 400000;

pair<int, int> road[max_K];
int fenwick[max_N + 1];

void update(int i) {
    while (i <= max_N) {
        ++fenwick[i];
        i += i & -i;
    }
}
int query(int i) {
    int ret = 0;
    while (i) {
        ret += fenwick[i];
        i -= i & -i;
    }
    return ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T; cin >> T;
    int t = 0;
start:;
    int N, M, K; cin >> N >> M >> K;
    for (int i = 0; i < K; ++i)
        cin >> road[i].first >> road[i].second;
    sort(road, road + K);

    memset(fenwick, 0, sizeof(fenwick));
    long long ans = 0;
    for (int i = 0; i < K; ++i) {
        auto [u, v] = road[i];
        ans += query(max_N) - query(v);
        update(v);
    }
    cout << "Test case " << ++t << ": " << ans << '\n';
    if (t ^ T) goto start;
    return 0;
}