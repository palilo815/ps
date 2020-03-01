#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    map<string, int> mp;
    string s;
    int total = 0;
    while (getline(cin, s)) {
        ++total;
        if (mp.find(s) == mp.end()) mp[s] = 1;
        else ++mp[s];
    }
    for (auto [tr, cnt] : mp)
        cout << tr << ' ' << fixed << setprecision(4) << 100.0 * cnt / total << '\n';
    return 0;
}