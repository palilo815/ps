#include <bits/stdc++.h>
#define all(v) v.begin(),v.end()
using namespace std;

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;

    vector<string> lz, vt;
    for (int i = 0; i < N; ++i) {
        string s; cin >> s;
        s[0] == '0' ? lz.emplace_back(s) : vt.emplace_back(s);
    }

    if (lz.empty()) {
        sort(all(vt), [&](auto & a, auto & b) {
            return a + b < b + a;
        });
        for (auto& x : vt) cout << x;
        return 0;
    }
    if (vt.empty()) {cout << "INVALID"; return 0;}

    sort(all(lz), [&](auto & a, auto & b) {
        return a + b < b + a;
    });
    swap(vt[0], *min_element(all(vt), [&](auto & a, auto & b) {
        return a + lz[0] + b < b + lz[0] + a;
    }));

    vt.insert(vt.end(), all(lz));
    sort(vt.begin() + 1, vt.end(), [&](auto & a, auto & b) {
        return a + b < b + a;
    });

    for (auto& x : vt) cout << x;
    return 0;
}