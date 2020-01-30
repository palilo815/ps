#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
const int max_N = 1000;

char block[max_N];
int DP[max_N];
char next_block(char c)
{
    if (c == 'B') return 'O';
    if (c == 'O') return 'J';
    return 'B';
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    loop(i, N) cin >> block[i];
    loop(i, N) DP[i] = INT_MAX;
    DP[0] = 0;

    loop(i, N) {
        // 갈 수 없는 블록이면 pass
        if (DP[i] == INT_MAX) continue;

        // i에서 j로 점프한다.
        char x = next_block(block[i]);
        for (int j = i + 1; j < N; ++j)
            if (block[j] == x)
                DP[j] = min(DP[j], DP[i] + (j - i) * (j - i));
    }

    if (DP[N - 1] == INT_MAX) cout << -1;
    else cout << DP[N - 1];
    return 0;
}