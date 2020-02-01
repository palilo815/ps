#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
const int max_N = 1000000;

int arr[max_N];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n; cin >> n;
    loop(i, n) cin >> arr[i];
    sort(arr, arr + n);
    loop(i, n) cout << arr[i] << '\n';
    return 0;
}