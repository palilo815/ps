#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n;
    double A, B, dow, toping[100];
    cin >> n >> A >> B >> dow;
    loop(i, n) cin >> toping[i];
    sort(toping, toping + n, greater<int>());
    double Ans = dow / A, Sum = 0;
    loop(i, n) {
        double tmp = (dow + Sum + toping[i]) / (A + (double)(i + 1) * B);
        if (tmp < Ans) break;
        Ans = tmp;
        Sum += toping[i];
    }
    cout << (int)Ans;
    return 0;
}