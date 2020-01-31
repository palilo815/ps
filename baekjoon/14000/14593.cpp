#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

typedef struct {
    int score;
    int submit;
    int last;
} info;
bool cmp(info& winner, info& i)
{
    if (winner.score == i.score) {
        if (winner.submit == i.submit)
            return winner.last > i.last;
        return winner.submit > i.submit;
    }
    return winner.score < i.score;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n; cin >> n;
    int idx = 1;
    info winner, tmp;
    cin >> winner.score >> winner.submit >> winner.last;

    for (int i = 2; i <= n; ++i) {
        cin >> tmp.score >> tmp.submit >> tmp.last;
        if (cmp(winner, tmp)) {
            winner = tmp;
            idx = i;
        }
    }
    cout << idx;
    return 0;
}