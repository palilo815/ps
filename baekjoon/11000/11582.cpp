#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 1 << 20;
int arr[max_N];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, k;
    cin >> n;
    loop(i, n) cin >> arr[i];
    cin >> k;
    int gap = n / k;
    for (int i = 0; i < n; i += gap)
        sort(arr + i, arr + i + gap);
    loop(i, n) cout << arr[i] << ' ';
    return 0;
}