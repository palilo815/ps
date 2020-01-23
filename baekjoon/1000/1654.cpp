#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define ll long long

int Lan[10000], k, n;
bool Make(ll m)
{
    int cnt = 0;
    loop(i, k)
        cnt += Lan[i] / m;
    if (cnt >= n) return true;
    else return false;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> k >> n;
    loop(i, k) cin >> Lan[i];
    ll s = 0, e = (1 << 31) - 1, m, ans = 0;
    while (s <= e) {
        m = s + (e - s) / 2;
        if (Make(m)) {
            ans = m;
            s = m + 1;
        }
        else
            e = m - 1;
    }
    cout << ans;
    return 0;
}