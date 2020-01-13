#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int Rev(int n)
{
    int ret = 0;
    while (n) {
        ret *= 10;
        ret += n % 10;
        n /= 10;
    }
    return ret;
}

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int x, y;
    cin >> x >> y;
    cout << Rev(Rev(x) + Rev(y));
    return 0;
}