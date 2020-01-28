#include <iostream>
#include <string.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int t, cnt[26];
    string s1, s2;
    cin >> t;
    while (t--) {
        memset(cnt, 0, sizeof(cnt));
        cin >> s1 >> s2;
        for (char c : s1) ++cnt[c - 'a'];
        for (char c : s2) --cnt[c - 'a'];
        bool f = true;
        loop(i, 26)
            if (cnt[i]) f = false;
        if (f) cout << "Possible\n";
        else cout << "Impossible\n";
    }
    return 0;
}