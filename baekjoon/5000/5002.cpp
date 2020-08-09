#include <bits/stdc++.h>
using namespace std;

char s[101];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int X; cin >> X >> s;
    int i = 0;
    for (int cur = 0; s[i]; ++i) {
        if (cur == X && s[i] == 'M') {
            if (s[i + 1] == 'W') s[i + 1] = 'M', --cur;
            else break;
        }
        else if (cur == -X && s[i] == 'W') {
            if (s[i + 1] == 'M') s[i + 1] = 'W', ++cur;
            else break;
        }
        else s[i] == 'M' ? ++cur : --cur;
    }
    cout << i;
    return 0;
}