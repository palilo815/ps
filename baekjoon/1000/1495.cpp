#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

bool DP[2][1001];
// DP[n][M] : n번 곡을 M의 볼륨으로 연주 가능한가?
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, s, m, x;
    cin >> n >> s >> m;
    DP[0][s] = true;
    loop(i, n) {
        cin >> x;
        int curr = i % 2, next = 1 - curr;
        loop(j, 1001) {
            if (DP[curr][j]) {
                DP[curr][j] = false;
                if (j + x <= m) DP[next][j + x] = true;
                if (j - x >= 0) DP[next][j - x] = true;
            }
        }
    }
    int FIN = n % 2;
    bool find = false;
    for (int i = 1000; i >= 0; --i)
        if (DP[FIN][i]) {
            cout << i;
            find = true;
            break;
        }
    if (!find) cout << -1;
    return 0;
}