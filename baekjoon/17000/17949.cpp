#include <bits/stdc++.h>
using namespace std;

char s[1000001], t[10];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N;
    cin >> s >> N;
    for (int i = 0, j; N--;) {
        cin >> t;
        if (t[0] == 'c')
            j = i + 2;
        else if (t[0] == 'i')
            j = i + 8;
        else
            j = i + 16;

        unsigned long long num = 0;
        while (i < j) {
            num = 16 * num + (s[i] < 'a' ? (s[i] - '0') : (s[i] - 'a' + 10));
            ++i;
        }
        cout << num << ' ';
    }
    return 0;
}