#include <bits/stdc++.h>
using namespace std;

int main()
{
    int a, b, c;
    string ans;
    while (1) {
        cin >> a >> b >> c;
        if (a == 0) break;
        int max_len = max(a, b);
        max_len = max(max_len, c);
        ans = (max_len * max_len == -max_len * max_len + a * a + b * b + c * c) ? "right" : "wrong";
        cout << ans << '\n';
    }
    return 0;
}