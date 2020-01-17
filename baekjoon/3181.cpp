#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string no_use[10] = { "i", "pa", "te","ni","niti","a","ali","nego","no","ili" };
    string s, ans = "";
    getline(cin, s);
    int len = s.size();
    ans += s[0] - 'a' + 'A';
    loop(i, len)
        if (s[i] == ' ') {
            int j = i + 1;
            while (s[j] != ' ' && j < len) ++j;
            string tmp = s.substr(i + 1, j - i - 1);
            bool f = false;
            loop(k, 10)
                if (tmp == no_use[k]) {
                    f = true;
                    break;
                }
            if (!f)
                ans += s[i + 1] - 'a' + 'A';
        }
    cout << ans;
    return 0;
}