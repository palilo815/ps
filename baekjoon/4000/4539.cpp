#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        int Num; cin >> Num;
        int Dig = 10;
        while (Num > Dig) {
            int tmp = Num % Dig;
            while (tmp >= 10) tmp /= 10;
            if (tmp >= 5) Num += Dig;
            Num = Num / Dig * Dig;
            Dig *= 10;
        }
        cout << Num << '\n';
    }
    return 0;
}