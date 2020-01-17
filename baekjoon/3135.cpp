#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    int A, B, n, arr[5];
    cin >> A >> B >> n;
    loop(i, n) cin >> arr[i];

    int ans = abs(A - B);
    loop(i, n)
        ans = min(ans, 1 + abs(B - arr[i]));
    cout << ans;
    return 0;
}