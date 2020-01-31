#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

string M[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int cnt[12];
    int N, TC = 0;
    while (cin >> N) {
        if (N == 0) break;
        memset(cnt, 0, sizeof(cnt));
        while (N--) {
            int d, m, y;
            cin >> d >> m >> y;
            ++cnt[m - 1];
        }
        cout << "Case #" << ++TC << ":\n";
        loop(i, 12)
            cout << M[i] << ':' << string(cnt[i], '*') << '\n';
    }
    return 0;
}