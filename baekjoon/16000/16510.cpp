#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int n, m;
    cin >> n >> m;

    vector<int> psum(n);
    for (auto& x : psum) cin >> x;
    partial_sum(psum.begin(), psum.end(), psum.begin());

    for (int x; m--;) {
        cin >> x;
        cout << upper_bound(psum.begin(), psum.end(), x) - psum.begin() << '\n';
    }
}