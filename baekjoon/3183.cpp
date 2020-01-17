#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int Days[13] = { 29,31,28,31,30,31,30,31,31,30,31,30,31 };
    int d, m, y;
    while (1) {
        cin >> d >> m >> y;
        if (d + m + y == 0) break;
        bool F = true;
        if (m < 1 || m > 12) F = false;
        else if (d < 1) F = false;
        else {
            if (m == 2) {
                if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) m = 0;
                if (d > Days[m]) F = false;
            }
            else
                if (d > Days[m]) F = false;
        }
        if (F) cout << "Valid\n";
        else cout << "Invalid\n";
    }
    return 0;
}