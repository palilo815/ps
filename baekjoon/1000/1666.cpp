#include <bits/stdc++.h>
using namespace std;
struct rec {
    int x, y, id;
};

const int max_N = 1e5;
const int Y = 1e5 + 1;

int dp[max_N];
rec arr[max_N << 1];
int segT[Y << 1];

void update(int i, int v) {
    if (segT[i += Y] >= v) return;
    for (segT[i] = v; i > 1; i >>= 1)
        segT[i >> 1] = max(segT[i], segT[i ^ 1]);
}
int query(int i) {
    int ret = 0;
    for (int l = Y, r = i + Y; l < r; l >>= 1, r >>= 1) {
        if (l & 1) ret = max(ret, segT[l++]);
        if (r & 1) ret = max(ret, segT[--r]);
    }
    return ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    for (int i = 0; i < N; ++i) {
        cin >> arr[i << 1].x >> arr[i << 1].y
            >> arr[i << 1 | 1].x >> arr[i << 1 | 1].y;
        arr[i << 1].id = arr[i << 1 | 1].id = i;
    }
    sort(arr, arr + (N << 1), [&](rec & a, rec & b) -> bool {
        return a.x == b.x ? a.y > b.y : a.x < b.x;
    });

    for (int i = 0; i < N << 1; ++i) {
        auto& [x, y, id] = arr[i];
        if (dp[id]) update(y, dp[id]);
        else dp[id] = query(y) + 1;
    }
    cout << *max_element(dp, dp + N);
    return 0;
}