#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define ll long long
using namespace std;
bool make_8(int n)
{
    while (n) {
        if (n % 10 >= 8) return false;
        n /= 10;
    }
    return true;
}
ll conv(ll n, ll dec)
{
    ll ret = 0, pos = 0;
    while (n) {
        ret += (n % 10) * pow(dec, pos);
        n /= 10;
        ++pos;
    }
    return ret;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        int t, num;
        cin >> t >> num;
        cout << t;
        if (make_8(num)) cout << ' ' << conv(num, 8);
        else cout << " 0";
        cout << ' ' << num << ' ' << conv(num, 16) << '\n';
    }
    return 0;
}