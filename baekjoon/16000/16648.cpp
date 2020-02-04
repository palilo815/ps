#include <bits/stdc++.h>
using namespace std;

int main()
{
    double t, p, rate;	//rate : 1%소모에 걸리는 시간
    scanf("%lf %lf", &t, &p);
    if (p >= 20) rate = t / (100.0 - p);
    else rate = t / (120.0 - 2.0 * p);

    double ans = 0;
    ans += max(0.0, p - 20.0) * rate;
    p = min(p, 20.0);
    ans += p * rate * 2.0;
    printf("%.8lf", ans);
    return 0;
}