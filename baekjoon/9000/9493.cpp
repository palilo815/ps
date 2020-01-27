#include <bits/stdc++.h>
using namespace std;

int main()
{
    double D, Tr, Ar;
    while (1) {
        cin >> D >> Tr >> Ar;
        if (D == 0) break;
        double T_tr = D * 3600 / Tr, T_ar = D * 3600 / Ar;
        double gap = abs(T_tr - T_ar);
        int s = (int)(gap + 0.5);
        int m = s / 60; s %= 60;
        int h = m / 60; m %= 60;
        cout << h << ':';
        cout << setfill('0') << setw(2) << m << ':';
        cout << setfill('0') << setw(2) << s << '\n';
    }
    return 0;
}