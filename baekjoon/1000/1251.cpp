#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    // '~' : ASCII value가 모든 알파벳보다 크다.
    string s, ans = "~";
    cin >> s;
    int len = s.size();
    for (int i = 1; i < len - 1; ++i) {
        for (int j = i + 1; j < len; ++j) {
            string tmp = s;
            reverse(tmp.begin(), tmp.begin() + i);
            reverse(tmp.begin() + i, tmp.begin() + j);
            reverse(tmp.begin() + j, tmp.end());
            if (tmp < ans) ans = tmp;
        }
    }
    cout << ans;
    return 0;
}