#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int T[100];
int main()
{
    cin.tie(NULL); cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, k; cin >> n >> k;
    loop(i, n) cin >> T[i];

    int ans = INT32_MIN;
    loop(i, n - k + 1) {
        int sum = 0;
        loop(j, k) sum += T[i + j];
        ans = max(ans, sum);
    }
    cout << ans;
    return 0;
}