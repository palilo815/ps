#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s1, s2;
    getline(cin, s1);
    getline(cin, s2);
    int ans = 0;
    size_t loc = 0;
    while (1) {
        loc = s1.find(s2, loc);
        if (loc == string::npos) break;
        ++ans;
        loc += s2.size();
    }
    cout << ans;
    return 0;
}