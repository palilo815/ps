#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int h, m, t;
    cin >> h >> m >> t;
    m += t;
    h += (m / 60), m %= 60;
    h %= 24;
    cout << h << ' ' << m;
    return 0;
}