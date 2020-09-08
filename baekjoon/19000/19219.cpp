#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    string s; cin >> s;
    int ans = 0;
    for (int i = 0, j = s.size() - 1, i0, j0; i <= j;) {
        if (s[i] ^ s[j]) {cout << 0; return 0;}
        for (i0 = i++; s[i] == s[i0]; ++i);
        for (j0 = j--; s[j] == s[j0]; --j);
        ans = i - i0 + j0 - j;
        if (ans < 3) {cout << 0; return 0;}
    }
    cout << ans / 2 + 1;
    return 0;
}