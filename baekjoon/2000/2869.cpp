#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);
    
    int up, down, dist; cin >> up >> down >> dist;
    int ans = (dist - up) / (up - down);
    dist -= (up - down) * ans;

    while (1) {
        dist -= up;
        ++ans;
        if (dist <= 0) break;
        dist += down;
    }
    cout << ans;
    return 0;
}