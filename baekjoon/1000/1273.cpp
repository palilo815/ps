#include <bits/stdc++.h>
using namespace std;

constexpr int mxCan = 1e6;
constexpr int lgN = 4194304;

int score[mxCan * 3], bit[lgN];

int kth(int k) {
    int s = 0;
    for (int len = lgN >> 1; len; len >>= 1)
        k < bit[s | len] ? --bit[s | len] : (k -= bit[s |= len]);
    return s;
}

int main(int argc, char* argv[]) {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    score[0] = n;
    vector<int> cnt(n);
    for (int i = 0, black; i < n; ++i) {
        cin >> black;
        ++score[cnt[i] += black];
    }
    for (int i = 0, grey; i < n; ++i) {
        cin >> grey;
        score[cnt[i] += grey] += 3;
    }
    for (int i = 0, white; i < n; ++i) {
        cin >> white;
        score[cnt[i] + white] -= 5;
    }

    partial_sum(score, score + mxCan * 3, score);

    for (int i = 1; i <= mxCan * 3; ++i)
        bit[i] = i & -i;

    int m;
    cin >> m;

    for (int h; m--;) {
        cin >> h, --h;
        cout << score[kth(h)] << '\n';
    }
}