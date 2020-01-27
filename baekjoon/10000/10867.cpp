#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 100000;
int arr[max_N];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n; cin >> n;
    loop(i, n) cin >> arr[i];
    sort(arr, arr + n);
    cout << arr[0];
    for (int i = 1; i < n; ++i)
        if (arr[i] != arr[i - 1])
            cout << ' ' << arr[i];
    return 0;
}