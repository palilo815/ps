#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    constexpr int MX_N = 1e6;
    vector<int64_t> psum(MX_N + 1, 1);
    psum[0] = 0;
    for (int i = 2; i <= MX_N; ++i) {
        for (int j = i; j <= MX_N; j += i) {
            psum[j] += i;
        }
    }
    partial_sum(psum.begin(), psum.end(), psum.begin());
    int T;
    cin >> T;
    for (int n; T--;) {
        cin >> n;
        cout << psum[n] << '\n';
    }
}