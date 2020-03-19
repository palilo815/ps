#include <bits/stdc++.h>
using namespace std;

int main() {
    string s; cin >> s;
    int T; cin >> T;
    while (T--) {
        int i, j; cin >> i >> j;
        swap(s[i], s[j]);
    }
    cout << s;
    return 0;
}