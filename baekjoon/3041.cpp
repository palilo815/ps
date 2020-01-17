#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int dist(char A, int r, int c)
{
    int pos_y, pos_x;
    if (A == '.') return 0;
    else {
        pos_y = (A - 'A') / 4;
        pos_x = (A - 'A') % 4;
    }
    return abs(r - pos_y) + abs(c - pos_x);
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    char B[4][4], b;
    int ans = 0;
    loop(i, 4) loop(j, 4) {
        cin >> b;
        ans += dist(b, i, j);
    }
    cout << ans;
    return 0;
}