#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define eps 1e-8

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T, cnt = 0;
    cin >> T;
    double len, wid, dep, weight;
    while (T-- > 0) {
        cin >> len >> wid >> dep >> weight;
        double sum = len + wid + dep;
        if (abs(sum - 125) < eps) sum = 125;
        bool f = true;
        if (((len <= 56 && wid <= 45 && dep <= 25) || sum <= 125) && weight <= 7) { cout << "1\n"; ++cnt; }
        else cout << "0\n";
    }
    cout << cnt;
    return 0;
}