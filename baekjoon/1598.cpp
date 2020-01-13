#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int a, b, dx, dy;
    cin >> a >> b;
    --a, --b;
    dx = (a / 4) - (b / 4);
    dy = (a % 4) - (b % 4);
    if (dx < 0) dx = -dx;
    if (dy < 0) dy = -dy;
    cout << dx + dy;
    return 0;
}