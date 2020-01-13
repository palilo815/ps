#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int cnt[26];
void print_str(vector<char>& vt, char c) {
    for (char x : vt) cout << x;
    if (c) cout << c;
    for (int i = vt.size() - 1; i >= 0; --i) cout << vt[i];
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    vector<char> vt;
    string s; cin >> s;
    loop(i, s.size()) ++cnt[s[i] - 'A'];

    // 홀수인 문자의 개수를 센다.
    int odd = 0;
    loop(i, 26) if (cnt[i] % 2) ++odd;

    // 만약에 odd == 1이면 홀수인 문자를 중앙에 넣어야 한다.
    if (odd <= 1) {
        // odd == 0인 경우
        // c는 그대로 '\0'인 상태로 남아있는다.
        char c = 0;
        loop(i, 26) {
            if (cnt[i] % 2 == 1) {
                c = i + 'A';
                --cnt[i];
            }
            int n = cnt[i] / 2;
            while (n--) vt.push_back(i + 'A');
        }
        print_str(vt, c);
    }
    // odd == 2면 불가능하다.
    else cout << "I'm Sorry Hansoo";
    return 0;
}