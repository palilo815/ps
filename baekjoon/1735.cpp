#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int gcd(int a, int b)
{
    if (a == 0) return b;
    return gcd(b % a, a);
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int a, b, c, d;
    cin >> a >> b >> c >> d;
    a = a * d + b * c;	// 분자
    b *= d;				// 분모

    // 약분
    int div = gcd(a, b);
    cout << a / div << ' ' << b / div;
    return 0;
}