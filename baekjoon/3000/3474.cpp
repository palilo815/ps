#include <bits/stdc++.h>
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);
    
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        int ans = 0;
        while (n) {
            n /= 5;
            ans += n;
        }
        cout << ans << '\n';
    }
    return 0;
}