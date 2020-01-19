#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int DP[2][3]; // 소중한 메모리 아껴쓰쟈
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, t = 0, tmp[3];
    while (cin >> N) {
        if (N == 0) break;

        // basis
        loop(i, 3) cin >> DP[0][i];
        // 출발점에서 (0,0)으로 갈 수 없으므로, (0,0)이 정답이 될수 없도록 INF를 넣는다.
        DP[0][0] = 1000000000;
        DP[0][2] += DP[0][1];


        for (int i = 1; i < N; ++i) {
            int id = i % 2;
            DP[id][0] = min(DP[1 - id][0], DP[1 - id][1]);
            DP[id][2] = min(DP[1 - id][1], DP[1 - id][2]);
            DP[id][1] = min(DP[id][0], DP[id][2]);

            loop(j, 3) cin >> tmp[j];
            loop(j, 3) DP[id][j] += tmp[j];

            DP[id][1] = min(DP[id][1], DP[id][0] + tmp[1]);
            DP[id][2] = min(DP[id][2], DP[id][1] + tmp[2]);
        }
        cout << ++t << ". " << DP[(N - 1) % 2][1] << '\n';
    }
    return 0;
}