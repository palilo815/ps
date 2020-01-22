#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int card[100][100], score[100];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, m; cin >> n >> m;
    loop(i, n) loop(j, m) cin >> card[i][j];
    loop(i, n) sort(card[i], card[i] + m, greater<int>());
    vector<int> winner;
    loop(i, m) {
        int	card_max = 0;
        loop(j, n) {
            if (card[j][i] > card_max) {
                winner.clear();
                card_max = card[j][i];
                winner.push_back(j);
            }
            else if (card[j][i] == card_max)
                winner.push_back(j);
        }
        for (int idx : winner) ++score[idx];
    }
    int score_max = 0;
    loop(i, n) {
        if (score[i] > score_max) {
            winner.clear();
            score_max = score[i];
            winner.push_back(i);
        }
        else if (score[i] == score_max)
            winner.push_back(i);
    }
    for (int idx : winner)
        cout << idx + 1 << ' ';
    return 0;
}