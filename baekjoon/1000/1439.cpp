#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s; cin >> s;
    int len = s.size(), one = 0, zero = 0;
    char prev = '\0';
    loop(i, len) {
        char c = s[i];
        if (c == prev) continue;
        if (c == '1') ++one;
        else ++zero;
        prev = c;
    }
    // one : 1로 이루어진 뭉치의 개수
    // zero : 0으로 이루어진 뭉치의 개수
    // ex) 1001100111 : 1뭉치 3개, 0뭉치 2개

    cout << min(one, zero);
    return 0;
}