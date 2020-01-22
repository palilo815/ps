#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int p[2], s[2];
    cin >> p[0] >> s[0];
    cin >> s[1] >> p[1];
    int P = p[0] + p[1], S = s[0] + s[1];
    if (P > S) cout << "Persepolis";
    else if (P < S) cout << "Esteghlal";
    else {
        if (p[1] > s[0]) cout << "Persepolis";
        else if (p[1] < s[0]) cout << "Esteghlal";
        else cout << "Penalty";
    }
    return 0;
}