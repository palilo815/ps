#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define ll long long

ll arr[10000];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n; cin >> n;
    loop(i, n) cin >> arr[i];
    sort(arr, arr + n);
    ll ans = 0;
    loop(i, n)
        ans += arr[i] * 2 * (2 * i - n + 1);
    cout << ans;
    return 0;
}