#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int M = 0, Y = 0, n, t;
    cin >> n;
    while (n--) {
        cin >> t;
        Y += 10 + (t / 30) * 10;
        M += 15 + (t / 60) * 15;
    }
    if (Y <= M) cout << "Y ";
    if (M <= Y) cout << "M ";
    cout << min(M, Y);
    return 0;
}