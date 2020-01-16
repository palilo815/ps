#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int key_cnt[26], s_cnt[26];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    string key; cin >> key;
    loop(i, key.size()) ++key_cnt[key[i] - 'A'];

    int ans = 0;
    while (N-- > 1) {
        memset(s_cnt, 0, sizeof(s_cnt));
        string s; cin >> s;
        loop(i, s.size()) ++s_cnt[s[i] - 'A'];

        int gap = 0;
        loop(i, 26)
            gap += abs(key_cnt[i] - s_cnt[i]);
        if (gap <= 2 && abs((int)s.size() - (int)key.size()) <= 1) ++ans;
    }
    cout << ans;
    return 0;
}