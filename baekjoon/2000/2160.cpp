#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

char Pnt[50][5][7];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, MIN = INT32_MAX;
    cin >> n;
    pair<int, int> Ans;
    loop(i, n) loop(j, 5) loop(k, 7)
        cin >> Pnt[i][j][k];
    loop(i, n - 1) {
        for (int j = i + 1; j < n; ++j) {
            //i번 그림과 j번 그림 비교
            int tmp = 0;
            loop(y, 5) loop(x, 7)
                if (Pnt[i][y][x] != Pnt[j][y][x]) tmp++;
            if (tmp < MIN) {
                MIN = tmp;
                Ans.first = i + 1, Ans.second = j + 1;
            }
        }
    }
    cout << Ans.first << ' ' << Ans.second;
    return 0;
}