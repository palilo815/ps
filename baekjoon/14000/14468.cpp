#include <bits/stdc++.h>
using namespace std;

bool appear[26];
int main()
{
    list<char> lst;
    int ans = 0, T = 52;
    char cow;
    while(T--) {
        cin >> cow;
        int c_num = cow - 'A';
        if (!appear[c_num]) {
            appear[c_num] = true;
            lst.push_back(cow);
        }
        else {
            int cnt = lst.size() - 1;
            auto it = lst.begin();
            while (*it != cow) ++it, --cnt;
            ans += cnt;
            lst.erase(it);
        }
    }
    cout << ans;
    return 0;
}