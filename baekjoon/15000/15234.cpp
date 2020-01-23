#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int arr[1000];
int main()
{
    int n, k; cin >> n >> k;
    loop(i, n) cin >> arr[i];
    sort(arr, arr + n);

    int ans = 0;
    loop(i, n - 1)
        if (binary_search(arr + i + 1, arr + n, k - arr[i]))
            ++ans;
    cout << ans;
    return 0;
}