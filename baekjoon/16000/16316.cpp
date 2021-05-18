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

    string s;
    for (int i = 1; i <= n; ++i) {
        cin >> s;
        if (s[0] == 'm') continue;
        else if (stoi(s) != i)
            return cout << "something is fishy", 0;
    }
    cout << "makes sense";
}