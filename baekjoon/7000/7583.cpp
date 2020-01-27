#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s;
    while (1) {
        getline(cin, s);
        if (s == "#") break;
        auto prev = s.begin();
        for (auto curr = s.begin(); curr != s.end(); ++curr)
            if (*curr == ' ') {
                if (prev + 1 < curr - 1)
                    reverse(prev + 1, curr - 1);
                prev = curr + 1;
            }
        reverse(prev + 1, s.end() - 1);
        cout << s << '\n';
    }
    return 0;
}