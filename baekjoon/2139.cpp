#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL); cout.tie(NULL);
    std::ios::sync_with_stdio(false);

    int DAY[13] = { 0,31,0,31,30,31,30,31,31,30,31,30,31 };
    int d, m, y;
    while (cin >> d >> m >> y) {
        if (d == 0) break;
        int Ans = 0;
        if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) DAY[2] = 29;
        else DAY[2] = 28;
        loop(i, m) Ans += DAY[i];
        Ans += d;
        cout << Ans << '\n';
    }
    return 0;
}