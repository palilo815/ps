#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n; cin >> n;
    while (n--) {
        string s; cin >> s;
        loop(i, s.size())
            if (s[i] < 'a')
                s[i] = s[i] - 'A' + 'a';
        cout << s << '\n';
    }
    return 0;
}