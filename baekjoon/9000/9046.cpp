#include<bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int cnt[26];
int main()
{
    string s;
    int T; cin >> T; cin.ignore();
    while (T-- > 0) {
        memset(cnt, 0, sizeof(cnt));
        getline(cin, s);
        for (char c : s) {
            if (c == ' ') continue;
            ++cnt[c - 'a'];
        }
        int max_cnt = -1, idx;
        bool dup = false;
        loop(i, 26) {
            if (cnt[i] == max_cnt) dup = true;
            else if (cnt[i] > max_cnt) {
                max_cnt = cnt[i];
                idx = i;
                dup = false;
            }
        }
        if (dup) cout << "?\n";
        else cout << (char)(idx + 'a') << '\n';
    }
    return 0;
}