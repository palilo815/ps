#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    int a = 0, b = 0, c = 0, t;
    cin >> t;
    if (t % 10) cout << "-1";
    else {
        a += t / 300; t %= 300;
        b += t / 60; t %= 60;
        c = t / 10;
        cout << a << ' ' << b << ' ' << c;
    }
    return 0;
}