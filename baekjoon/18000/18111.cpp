#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 500;

int h[max_N][max_N];

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int row, col, B; cin >> row >> col >> B;
    int s = 0, e = B;
    loop(i, row) loop(j, col) {
        cin >> h[i][j];
        e += h[i][j];
    }
    e /= row * col;
    // 모든 블럭을 다 사용하면 모든 땅의 높이를 e로 고르게 만들 수 있다.

    int min_cost = INT_MAX;
    int ans = -1;
    loop(i, e + 1) {
        int push = 0, pop = 0;
        loop(r, row) loop(c, col) {
            if (h[r][c] < i) push += i - h[r][c];
            else pop += h[r][c] - i;
        }
        int cost = push + pop * 2;
        if (cost <= min_cost) {
            min_cost = cost;
            ans = i;
        }
    }
    cout << min_cost << ' ' << ans;
    return 0;
}