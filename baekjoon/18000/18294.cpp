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
    vector<string> a(n);
    string s;
    int cnt = 0;
    for (auto& x : a) {
        cin >> x;
        if (x == s) {
            ++cnt;
        } else {
            cnt ? --cnt : (s = x, cnt = 1);
        }
    }
    cout << (count(a.begin(), a.end(), s) * 2 > n ? s : "NONE");
}