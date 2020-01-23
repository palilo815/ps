#include <bits/stdc++.h>
#define P pair<int,int>
using namespace std;
// 0 1
// 3 2
int frac[4];
int main()
{
    cin >> frac[0] >> frac[1] >> frac[3] >> frac[2];
    int ans;
    P max_val = { 0,1 }; // 분자 분모
    for (int rot = 0; rot < 4; ++rot) {
        int son = frac[(0 + rot) % 4] * frac[(2 + rot) % 4] + frac[(1 + rot) % 4] * frac[(3 + rot) % 4];
        int mom = frac[(2 + rot) % 4] * frac[(3 + rot) % 4];
        if (son * max_val.second > max_val.first* mom) {
            max_val = { son,mom };
            ans = (4 - rot) % 4;
        }
    }
    cout << ans;
    return 0;
}