#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    string s; getline(cin, s);
    int cnt[26] = {};
    for (char c : s) {
        if (c >= 'A' && c <= 'Z') ++cnt[c - 'A'];
        else if (c >= 'a' && c <= 'z') ++cnt[c - 'a'];
    }
    loop(i, 26)
        cout << (char)(i + 'A') << " | " << string(cnt[i], '*') << '\n';
    return 0;
}