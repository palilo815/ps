#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int A = 0, B = 0, t;
    cin >> t;
    while (t--) {
        int a, b; cin >> a >> b;
        if (a > b) ++A;
        if (a < b) ++B;
    }
    cout << A << ' ' << B;
    return 0;
}