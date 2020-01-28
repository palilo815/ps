#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

bool ans[26];
int cnt[26], sbm[26];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int t; char c; string s;
    while (1) {
        cin >> t;
        if (t == -1) break;
        cin >> c >> s;
        int num = c - 'A';
        if (s[0] == 'r') {
            ans[num] = true;
            sbm[num] = t;
        }
        else ++cnt[num];
    }
    int problem = 0, penalty = 0;
    loop(i, 26)
        if (ans[i]) {
            ++problem;
            penalty += sbm[i] + cnt[i] * 20;
        }
    cout << problem << ' ' << penalty;
    return 0;
}