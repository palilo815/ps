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

    vector<bool> is_lie(n);
    for (int i = 0; i < n; ++i) {
        char buf[6];
        cin >> buf;
        is_lie[i] = buf[0] == 'L';
    }

    reverse(is_lie.begin(), is_lie.end());

    bool lie = false;
    for (const auto x : is_lie)
        lie = x ^ lie;
    cout << (lie ? "LIE" : "TRUTH");
}