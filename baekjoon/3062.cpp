#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int REV(int n)
{
    int ret = 0;
    while (n) {
        ret *= 10;
        ret += n % 10;
        n /= 10;
    }
    return ret;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        int r = REV(n);
        if (n + r == REV(n + r)) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}