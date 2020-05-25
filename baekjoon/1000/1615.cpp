#include <bits/stdc++.h>
using namespace std;

const int max_N = 2000;

int N, M;
int fenwick[max_N + 1];
pair<int, int> edge[max_N * (max_N - 1) / 2];

void update(int i) {
    while (i <= N) {
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

    cin >> N >> M;
    for (int i = 0; i < M; ++i)
        cin >> edge[i].first >> edge[i].second;
    sort(edge, edge + M);

    long long ans = 0;
    for (int i = 0; i < M; ++i) {
        int v = edge[i].second;
        ans += query(N) - query(v);
        update(v);
    }
    cout << ans;
    return 0;
}