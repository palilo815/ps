#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);
    
    string name[20];
    int n; cin >> n;
    loop(i, n) cin >> name[i];
    bool inc = (name[0] < name[1]);
    for (int i = 1; i < n - 1; ++i)
        if (inc != (name[i] < name[i + 1])) {
            cout << "NEITHER";
            return 0;
        }
    if (inc) cout << "INCREASING";
    else cout << "DECREASING";
    return 0;
}