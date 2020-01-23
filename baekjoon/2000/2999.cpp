#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s; cin >> s;
    int len = s.size(), row, col;
    for (int i = 1; i * i <= len; ++i)
        if (len % i == 0) row = i;
    col = len / row;
    loop(i, row) for (int j = i; j < len; j += row)
        cout << s[j];
    return 0;
}