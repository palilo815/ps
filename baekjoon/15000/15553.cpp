#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, k;
    cin >> n >> k;
    vector<int> a(n - 1);
    {
        int prv, cur;
        cin >> prv;
        for (auto& x : a) {
            cin >> cur;
            x = cur - prv;
            prv = cur;
        }
    }
    sort(a.begin(), a.end());
    const auto res = accumulate(a.begin(), a.end() - (k - 1), 0);
    cout << res + k;
}