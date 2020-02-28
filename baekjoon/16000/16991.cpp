#include<bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int MAX = 16;
int N;
double cache[MAX][1 << MAX];
double x[MAX], y[MAX];

double dist(int a, int b) {
    double dx = x[a] - x[b], dy = y[a] - y[b];
    return sqrt(dx * dx + dy * dy);
}
double TSP(int u, int visited) {
    if (visited == (1 << N) - 1)
        return dist(u, 0);

    double& ret = cache[u][visited];
    if (ret) return ret;

    ret = 1e9;
    loop(v, N) if (!(visited & (1 << v)))
        ret = min(ret, dist(u, v) + TSP(v, visited + (1 << v)));
    return ret;
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> N;
    loop(i, N) cin >> x[i] >> y[i];
    cout << fixed << setprecision(9) << TSP(0, 1);
    return 0;
}