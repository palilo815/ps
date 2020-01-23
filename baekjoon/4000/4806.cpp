#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s;
    int cnt = 0;
    while (getline(cin, s)) ++cnt;
    cout << cnt;
    return 0;
}