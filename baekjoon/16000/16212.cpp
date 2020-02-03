#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
const int max_N = 500000;

int arr[max_N];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    loop(i, N) cin >> arr[i];
    sort(arr, arr + N);
    loop(i, N) cout << arr[i] << ' ';
    return 0;
}