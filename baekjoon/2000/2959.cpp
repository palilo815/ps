#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cin.tie(NULL);
    ios::sync_with_stdio(false);

    int arr[4];
    loop(i, 4) cin >> arr[i];
    sort(arr, arr + 4);
    cout << arr[0] * arr[2];
    return 0;
}