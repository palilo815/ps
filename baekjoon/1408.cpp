#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<=n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int h1, m1, s1, h2, m2, s2;
    char c;
    cin >> h1 >> c >> m1 >> c >> s1 >> h2 >> c >> m2 >> c >> s2;
    s2 -= s1;
    if (s2 < 0) s2 += 60, --m2;
    m2 -= m1;
    if (m2 < 0) m2 += 60, --h2;
    h2 -= h1;
    if (h2 < 0) h2 += 24;

    if (h2 < 10) cout << 0;
    cout << h2 << ':';
    if (m2 < 10) cout << 0;
    cout << m2 << ':';
    if (s2 < 10) cout << 0;
    cout << s2;
    return 0;
}