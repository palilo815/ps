#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, mch[10], num = 0;
    while (cin >> n) {
        if (n == 0) break;
        for (int i = 1; i <= n; ++i)
            cin >> mch[i];
        string name; int m;
        cout << "Machine " << ++num << '\n';
        while (cin >> name >> m) {
            if (name == "#") break;
            int sum = 0;
            while (m--) {
                int ind, t;
                cin >> ind >> t;
                sum += mch[ind] * t;
            }
            cout << name << ' ' << sum << '\n';
        }
    }
    return 0;
}