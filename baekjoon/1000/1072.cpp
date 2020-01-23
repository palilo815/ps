#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define ll long long

ll x, y, z;
bool Changed(ll a)
{
    if (100 * (y + a) / (x + a) == z) return false;
    return true;
}

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    while (cin >> x >> y) {
        z = 100 * y / x;

        // impossible : 99% -> 100%
        if (z >= 99) {
            cout << "-1\n";
            continue;
        }

        // binary search
        ll s = 1, e = 1000000000, m, ans;
        while (s <= e) {
            m = s + (e - s) / 2;
            if (Changed(m)) {
                ans = m;
                e = m - 1;
            }
            else s = m + 1;
        }
        cout << ans << '\n';
    }

    return 0;
}