#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 512;

int x[max_N], y[max_N];
double DP[max_N][max_N];

double dist(int a, int b) {
    double dx = x[a] - x[b], dy = y[a] - y[b];
    return sqrt(dx * dx + dy * dy);
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T; cin >> T;
    while (T--) {
        int N; cin >> N;
        loop(i, N) fill_n(DP[i], N, DBL_MAX);
        DP[0][0] = 0;

        cin >> x[0] >> y[0];
        for (int i = 1; i < N; ++i) {
            cin >> x[i] >> y[i];
            double d1 = dist(i, i - 1);
            DP[i][0] = DP[i - 1][0] + d1;

            loop(j, i - 1) {
                double d2 = dist(i, j);
                DP[i][j] = min(DP[i][j], DP[i - 1][j] + d1);
                DP[i][i - 1] = min(DP[i][i - 1], DP[i - 1][j] + d2);
            }
        }

        double ans = DBL_MAX;
        loop(i, N - 1)
            ans = min(ans, DP[N - 1][i] + dist(i, N - 1));
        cout << fixed << setprecision(8) << ans << '\n';
    }
    return 0;
}