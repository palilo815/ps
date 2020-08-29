#include <cstdio>

int N;
double l, w, h;

int solve(double m) {
    long long x = l / m, y = w / m, z = h / m;
    return x * y * z >= N;
}
int main() {
    scanf("%d%lf%lf%lf", &N, &l, &w, &h);

    double lo = 0, hi = 1e9;
    for (int i = 0; i < 10000; ++i) {
        double m = (lo + hi) / 2;
        solve(m) ? (lo = m) : (hi = m);
    }
    printf("%.10lf", lo);
    return 0;
}