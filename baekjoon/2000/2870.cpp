#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

bool my_comp(string & a, string & b) {
    int len_a = a.size(), len_b = b.size();
    if (len_a != len_b)
        return len_a < len_b;
    loop(i, len_a) {
        if (a[i] != b[i])
            return a[i] < b[i];
    }
    return false;
}
string num(string & s, int& pos, int len)
{
    string ret;
    while (pos < len && s[pos] == '0') ++pos;
    while (pos < len && s[pos] < 'A')
        ret += s[pos++];
    --pos;
    return ret;
}

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N;
    vector<string> vt;
    cin >> N;
    while (N--) {
        string s; cin >> s;
        int len = s.size();
        loop(i, len)
            if (s[i] < 'A') {
                string tmp = num(s, i, len);
                if (tmp == "") tmp = "0";
                vt.push_back(tmp);
            }
    }
    sort(vt.begin(), vt.end(), my_comp);
    for (string s : vt) cout << s << '\n';
    return 0;
}