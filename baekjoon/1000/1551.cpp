#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int arr[20];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, k;
    char x;
    cin >> n >> k;
    loop(i, n - 1) cin >> arr[i] >> x;
    cin >> arr[n - 1];

    loop(i, k) for (int j = n - 1; j > i; --j)
        arr[j] -= arr[j - 1];
    for (int i = k; i < n - 1; ++i)
        cout << arr[i] << ',';
    cout << arr[n - 1];
    return 0;
}