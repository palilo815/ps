#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define eps 1e-8 // 유효 오차
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    double c, a, b, k;
    cin >> c >> a >> b;
    k = sqrt(c * c / (a * a + b * b));
    int x = k;
    x++;
    if (x - k < eps) k = x;
    cout << (int)(a * k) << ' ' << (int)(b * k);
    return 0;
}