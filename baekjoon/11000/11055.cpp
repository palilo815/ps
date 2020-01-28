#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 1000;
int arr[max_N], DP[max_N];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    loop(i, N) cin >> arr[i];
    
    // basis : 길이가 1인 IS
    memcpy(DP, arr, sizeof(int) * N);
    loop(i, N)
        for (int j = i + 1;j < N;++j)
            if (arr[j] > arr[i])
                DP[j] = max(DP[j], DP[i] + arr[j]);
    
    int ans = 0;
    loop(i, N) ans = max(ans, DP[i]);
    cout << ans;
    return 0;
}