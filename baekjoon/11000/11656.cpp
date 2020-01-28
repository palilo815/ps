#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_len = 1000;
string postfix[max_len];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s; cin >> s;
    int len = s.size();
    loop(i, len) postfix[i] = s.substr(i, len);
    sort(postfix, postfix + len);
    loop(i, len) cout << postfix[i] << '\n';
    return 0;
}