#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int score[101][101], submit[101], last[101];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        memset(score, 0, sizeof(score));
        memset(submit, 0, sizeof(submit));
        memset(last, 0, sizeof(last));

        int N_team, N_pro, me, M;
        cin >> N_team >> N_pro >> me >> M;
        loop(i, M) {
            int idx, p, scr; cin >> idx >> p >> scr;
            score[idx][p] = max(score[idx][p], scr);
            ++submit[idx];
            last[idx] = i;
        }

        int my_scr = 0, better = 0;
        for (int i = 1; i <= N_pro; ++i) my_scr += score[me][i];
        for (int i = 1; i <= N_team; ++i) {
            if (i == me) continue;
            int tmp_scr = 0;
            for (int j = 1; j <= N_pro; ++j) tmp_scr += score[i][j];

            if (tmp_scr > my_scr) ++better;
            else if (tmp_scr == my_scr) {
                if (submit[i] < submit[me]) ++better;
                else if (submit[i] == submit[me] && last[i] < last[me]) ++better;
            }
        }
        // 나보다 잘한 팀 수 + 1 == 등수
        cout << better + 1 << '\n';
    }
    return 0;
}