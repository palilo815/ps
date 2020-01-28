#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 100000;
int arr[max_N];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, ans = INT_MAX;
    cin >> n;
    loop(i, n) cin >> arr[i];
    sort(arr, arr + n);
    loop(i, n / 2)
        ans = min(ans, arr[i] + arr[n - 1 - i]);
    cout << ans;
    return 0;
}