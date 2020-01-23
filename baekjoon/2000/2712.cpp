#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    int T; cin >> T;
    while (T--) {
        double val;
        string unit;
        cin >> val >> unit;
        if (unit == "kg") {
            val *= 2.2046;
            unit = "lb";
        }
        else if (unit == "lb") {
            val *= 0.4536;
            unit = "kg";
        }
        else if (unit == "l") {
            val *= 0.2642;
            unit = "g";
        }
        else {
            val *= 3.7854;
            unit = "l";
        }
        cout << fixed << setprecision(4) << val << ' ' << unit << '\n';
    }
    return 0;
}