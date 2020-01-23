#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define PI 3.14159265358979323846

int main()
{
    int Trip = 0;
    double D, Rot, T;
    while (cin >> D >> Rot >> T) {
        if (Rot == 0) break;
        double Dis = PI * D * Rot / 63360.0;
        double MPH = Dis / T * 3600.0;
        cout << fixed << setprecision(2) << "Trip #" << ++Trip << ": " << Dis << ' ' << MPH << '\n';
    }
    return 0;
}