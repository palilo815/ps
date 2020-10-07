#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    string s;
    int cnt = 0;
    getline(cin, s);
    for (;;) {
        getline(cin, s);
        if (s == "문제")
            ++cnt;
        else if (s == "고무오리")
            cnt ? --cnt : (cnt += 2);
        else
            break;
    }
    cout << (cnt ? "힝구" : "고무오리야 사랑해");
    return 0;
}