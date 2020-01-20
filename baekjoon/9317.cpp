#include<bits/stdc++.h>
using namespace std;
int main()
{
    double D, w, h, R_h, R_v;
    while (cin >> D >> R_h >> R_v) {
        if (D == 0) break;
        w = D * 16 / sqrt(337), h = D * 9 / sqrt(337);
        printf("Horizontal DPI: %.2lf\n", R_h / w);
        printf("Vertical DPI: %.2lf\n", R_v / h);
    }
    return 0;
}