#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n, k; cin >> n >> k;
    int ans = n;
    for(int i=1; i<=k; ++i)
        ans += n * pow(10, i);
    cout << ans;
    return 0;
}