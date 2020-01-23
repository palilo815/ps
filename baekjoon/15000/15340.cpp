#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int c, d;
    while (cin >> c >> d) {
        if (!c && !d) break;
        int cost[3];
        loop(i, 3) cost[i] = (30 + 5 * i) * c + (40 - 10 * i) * d;
        sort(cost, cost + 3);
        cout << cost[0] << '\n';
    }
    return 0;
}