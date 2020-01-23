#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int hide[101][101];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, m, Ans = 0;
    cin >> n >> m;
    while (n--) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        for (int i = y1; i <= y2; ++i)
            for (int j = x1; j <= x2; ++j)
                ++hide[i][j];
    }
    for (int i = 1; i <= 100; ++i)
        for (int j = 1; j <= 100; ++j)
            if (hide[i][j] > m)
                ++Ans;
    cout << Ans;
    return 0;
}