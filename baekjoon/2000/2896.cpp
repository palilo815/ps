#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define eps 1e-9
using namespace std;

int main()
{
    int buy[3], need[3];
    loop(i, 3) cin >> buy[i];
    loop(i, 3) cin >> need[i];

    double best = 0;
    loop(i, 3) {
        double t = 1.0 * buy[i] / need[i];
        if (t > best) {
            loop(j, 3)
                if (buy[j] - need[j] * t < -eps) goto OUT;
            best = t;
        }
    OUT:;
    }
    cout << fixed << setprecision(8)
        << buy[0] - need[0] * best << ' ' << buy[1] - need[1] * best << ' ' << buy[2] - need[2] * best;
    return 0;
}