#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int DP[2][2][3];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    for (int i = 1;i <= N;++i) {
        int a, b, c; cin >> a >> b >> c;
        int here = i % 2, up = 1 - (i % 2);
        
        int L_max = max(DP[0][up][0], DP[0][up][1]);
        int R_max = max(DP[0][up][1], DP[0][up][2]);
        int L_min = min(DP[1][up][0], DP[1][up][1]);
        int R_min = min(DP[1][up][1], DP[1][up][2]);
        
        // DP[0] : 최댓값 저장
        DP[0][here][0] = L_max + a;
        DP[0][here][1] = max(L_max, R_max) + b;
        DP[0][here][2] = R_max + c;

        // DP[1] : 최솟값 저장
        DP[1][here][0] = L_min + a;
        DP[1][here][1] = min(L_min, R_min) + b;
        DP[1][here][2] = R_min + c;
    }

    int Min = INT_MAX, Max = 0;
    loop(i, 3) {
        Min = min(Min, DP[1][N % 2][i]);
        Max = max(Max, DP[0][N % 2][i]);
    }
    cout << Max << ' ' << Min;
    return 0;
}