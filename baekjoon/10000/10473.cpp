#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 101;

double X[max_N], Y[max_N];
double dist[max_N];
bool v[max_N];

double func(double x1, double y1, double x2, double y2) {
    double dx = x1 - x2, dy = y1 - y2;
    double d = sqrt(dx * dx + dy * dy);
    return min(d / 5, fabs(d - 50) / 5 + 2);
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    double sx, sy, dx, dy;
    int N;
    cin >> sx >> sy >> dx >> dy >> N;
    loop(i, N) cin >> X[i] >> Y[i];

    X[N] = dx, Y[N] = dy;
    ++N;

    loop(i, N) {
        double _dx = sx - X[i], _dy = sy - Y[i];
        dist[i] = sqrt(_dx * _dx + _dy * _dy) / 5;
    }

    while (1) {
        int k = -1;
        loop(i, N) if (!v[i] && (k == -1 || dist[i] < dist[k]))
            k = i;

        assert(k >= 0);
        if (k == N - 1) {
            cout << fixed << setprecision(5) << dist[k];
            return 0;
        }

        v[k] = true;
        loop(i, N) if (!v[i]) {
            double d = func(X[k], Y[k], X[i], Y[i]);
            if (dist[i] > d + dist[k])
                dist[i] = d + dist[k];
        }
    }
    return 0;
}