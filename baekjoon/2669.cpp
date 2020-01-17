#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int arr[101][101];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    loop(i, 4) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        for (int a = x1; a < x2; ++a)
            for (int b = y1; b < y2; ++b)
                arr[a][b] = 1;
    }

    int ans = 0;
    loop(i, 101) loop(j, 101)
        if (arr[i][j]) ++ans;
    cout << ans;
    return 0;
}