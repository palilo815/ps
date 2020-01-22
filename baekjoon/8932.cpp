#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

double a[7][3] = { {9.23076, 26.7, 1.835 },{1.84523 ,75 ,1.348 },{56.0211, 1.5 ,1.05 },{4.99087 ,42.5 ,1.81 },{0.188807, 210, 1.41 },{15.9803 ,3.8, 1.04 },{0.11193 ,254 ,1.88 } };
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int t; cin >> t;
    double P[7];
    while (t--) {
        loop(i, 7) cin >> P[i];
        int S = 0;
        loop(i, 7)
            S += (int)(a[i][0] * pow(abs(P[i] - a[i][1]), a[i][2]));
        cout << S << '\n';
    }
    return 0;
}