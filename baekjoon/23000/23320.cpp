#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) {
        cin >> x;
    }
    int m;
    cin >> m;
    cout << n * m / 100 << ' ';
    cin >> m;
    cout << count_if(a.begin(), a.end(), [&](const auto& x) {
        return x >= m;
    });
}