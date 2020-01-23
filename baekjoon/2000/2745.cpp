#include<bits/stdc++.h>
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s;
    int n, ans = 0, D = 1;
    cin >> s >> n;
    for (int i = s.size() - 1; i >= 0; --i) {
        if (s[i] < 'A') ans += (s[i] - '0') * D;
        else ans += (s[i] - 'A' + 10) * D;
        D *= n;
    }
    cout << ans;
    return 0;
}