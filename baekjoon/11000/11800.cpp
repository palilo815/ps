#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string Nick[6] = { "Yakk","Doh","Seh","Ghar","Bang","Sheesh" };
    string Same[6] = { "Habb Yakk","Dobara","Dousa","Dorgy","Dabash","Dosh" };
    int t, a, b;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        cin >> a >> b;
        cout << "Case " << i << ": ";
        if (a == b) cout << Same[a - 1];
        else {
            if (a > b) swap(a, b);
            if (b == 6 && a == 5) cout << "Sheesh Beesh";
            else cout << Nick[b - 1] << ' ' << Nick[a - 1];
        }
        cout << '\n';
    }
    return 0;
}