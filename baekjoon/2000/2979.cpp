#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int truck[101];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int a, b, c;
    cin >> a >> b >> c;
    loop(i, 3) {
        int s, e; cin >> s >> e;
        for (int i = s; i < e; ++i)
            ++truck[i];
    }

    int cost = 0;
    loop(i, 101) {
        if (truck[i] == 1) cost += a;
        else if (truck[i] == 2) cost += 2 * b;
        else if (truck[i] == 3) cost += 3 * c;
    }
    cout << cost;
    return 0;
}