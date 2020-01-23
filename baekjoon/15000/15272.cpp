#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s; cin >> s;
    bool f = false;
    loop(i, s.size() - 1)
        if (s[i] == 's' && s[i + 1] == 's') f = true;
    if (f) cout << "hiss";
    else cout << "no hiss";
    return 0;
}