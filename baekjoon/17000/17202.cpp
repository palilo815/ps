#include <bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    string a, b; cin >> a >> b;
    vector<int> vt;
    loop(i, 8) {
        vt.push_back(a[i] - '0');
        vt.push_back(b[i] - '0');
    }
    int len = 15;
    while (len > 1) {
        loop(i, len)
            vt[i] = (vt[i] + vt[i + 1]) % 10;
        --len;
    }
    loop(i, 2) cout << vt[i];
    return 0;
}