#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s;
    getline(cin, s);
    int len = s.size();
    loop(i, len) {
        if (s[i] == '<') {
            int j = i + 1;
            while (s[j] != '>') ++j;
            for (int pos = i; pos <= j; ++pos)
                cout << s[pos];
            i = j;
        }
        else {
            int j = i + 1;
            while (s[j] != ' ' && s[j] != '<' && j < len) ++j;
            for (int pos = j - 1; pos >= i; --pos)
                cout << s[pos];
            if (j != len && s[j] == ' ') { cout << ' '; i = j; }
            else i = j - 1;
        }
    }
    return 0;
}