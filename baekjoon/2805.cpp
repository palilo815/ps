#include <bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define ll long long

ll tree[1000000];
bool enough(int N, int h, ll cut)
{
    ll sum = 0;
    loop(i, N)
        if (tree[i] > cut)
            sum += (tree[i] - cut);
    if (sum >= h) return true;
    else return false;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, h; cin >> N >> h;
    loop(i, N) cin >> tree[i];

    ll s = 0, e = 1000000000, ans;
    while (s <= e) {
        ll mid = s + (e - s) / 2;
        if (enough(N, h, mid)) {
            ans = mid;
            s = mid + 1;
        }
        else
            e = mid - 1;
    }
    cout << ans;
    return 0;
}