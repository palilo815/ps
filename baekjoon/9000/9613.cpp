#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int gcd(int a, int b)
{
    if (a == 0)
        return b;
    return gcd(b % a, a);
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T, N, arr[100];
    cin >> T;
    while (T--) {
        long long ans = 0;
        cin >> N;
        loop(i, N) cin >> arr[i];
        loop(i, N - 1) for (int j = i + 1; j < N; ++j)
            ans += gcd(arr[i], arr[j]);
        cout << ans << '\n';
    }
    return 0;
}