#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string T[2], ter = "00:00";
    while (cin >> T[0] >> T[1]) {
        if (T[0] == ter && T[1] == ter) break;
        int add = 0, h = 0, m = 0;
        loop(i, 2) {
            h += (T[i][0] - '0') * 10 + T[i][1] - '0';
            m += (T[i][3] - '0') * 10 + T[i][4] - '0';
        }
        if (m >= 60) m -= 60, ++h;
        while (h >= 24) h -= 24, ++add;
        cout << setfill('0') << setw(2) << h << ':' << setfill('0') << setw(2) << m;
        if (add) cout << " +" << add;
        cout << '\n';
    }
    return 0;
}