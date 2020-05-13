#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 17;

int N;
string board;
int rabbit[max_N];
vector<int> tmp[max_N];

int solve(int mask, int N) {
    memset(rabbit, -1, sizeof(int) * N);
    loop(i, N) if (mask & (1 << i))
        rabbit[i] = -2;

    while (N > 2) {
        loop(i, N) if (rabbit[i] != -1) {
            rabbit[i] = -1;
            if (i == 0) tmp[1].emplace_back(i);
            else if (i >= N - 2) tmp[i - 1].emplace_back(i);
            else switch (board[i]) {
            case 'W': tmp[i - 1].emplace_back(i); break;
            case 'B': tmp[i + 1].emplace_back(i); break;
            case 'R':
                if (rabbit[i] == -2) tmp[i - 1].emplace_back(i);
                else tmp[i + 1].emplace_back(i);
            }
        }
        loop(i, N) {
            if (tmp[i].size() == 1)
                rabbit[i] = tmp[i][0];
            tmp[i].clear();
        }
        --N;
    }

    int ret = 0;
    loop(i, N) if (rabbit[i] != -1)
        ++ret;
    return ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> board;
    N = board.size();

    int R; cin >> R;
    int mask = (1 << R) - 1;
    int E = (1 << N) - 1;

    int A = 0, B = 0;
    while (mask <= E) {
        A += 1;
        B += solve(mask, N);

        int t = mask | (mask - 1);
        mask = (t + 1) | (((~t & -~t) - 1) >> (__builtin_ctz(mask) + 1));
    }
    cout << fixed << setprecision(10)
         << 1.0 * B / A;
    return 0;
}