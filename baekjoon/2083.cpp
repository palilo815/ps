#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s, Ans[2] = { "Junior","Senior" };
    int a, w;
    while (cin >> s >> a >> w) {
        if (s == "#") break;
        cout << s << ' ';
        int category = (a > 17 || w >= 80);
        cout << Ans[category] << '\n';
    }
    return 0;
}