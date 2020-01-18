#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s; cin >> s;
    int len = s.size();
    bool java = false, cpp = false;
    loop(i, len) {
        if (s[i] == '_') cpp = true;
        else if (s[i] <= 'Z') java = true;
    }

    // error str이면 java랑 cpp 둘 다 true로 만들어버림
    if (java && !cpp)
        if (s[0] <= 'Z') cpp = true;
    if (!java && cpp) {
        if (s[0] == '_' || s[len - 1] == '_') java = true;
        loop(i, len - 1)
            if (s[i] == '_' && s[i + 1] == '_') java = true;
    }

    if (java && cpp) cout << "Error!";
    else if (!java && !cpp) cout << s;
    else if (java) {
        loop(i, len) {
            if (s[i] <= 'Z') cout << '_' << (char)(s[i] + 32);
            else cout << s[i];
        }
    }
    else {
        loop(i, len) {
            if (s[i] == '_') {
                s[i + 1] -= 32;
                continue;
            }
            cout << s[i];
        }
    }
    return 0;
}