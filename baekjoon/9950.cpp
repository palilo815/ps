#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    int a, b, c;
    while (cin >> a >> b >> c) {
        if (a == 0 && b == 0) break;
        if (a == 0) a = c / b;
        else if (b == 0) b = c / a;
        else c = a * b;
        cout << a << ' ' << b << ' ' << c << '\n';
    }
    return 0;
}