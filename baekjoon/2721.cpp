#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int sum(int n)
{
    return n * (n + 1) / 2;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);
    
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        int W = 0;
        for (int i = 1; i <= n; ++i)
            W += i * sum(i + 1);
        cout << W << '\n';
    }
    return 0;
}