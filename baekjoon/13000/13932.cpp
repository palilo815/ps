#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    vector<int> a(n);
    for (auto& x : a) cin >> x;

    int mx = max_element(a.begin(), a.end()) - a.begin();
    int total = accumulate(a.begin(), a.end(), 0);

    if (a[mx] * 2 > total) cout << "impossible";
    else {
        cout << mx + 1;
        for (int i = 0; i < n; ++i)
            if (i != mx)
                cout << ' ' << i + 1;
    }
}