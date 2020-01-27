#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

bool legal(string& s)
{
    stack<char> stk;
    int len = s.size();
    loop(i, len) {
        char c = s[i];
        if (c == '(' || c == '{' || c == '[') stk.push(c);
        else if (c == ')') {
            if (stk.empty() || stk.top() != '(') return false;
            stk.pop();
        }
        else if (c == '}') {
            if (stk.empty() || stk.top() != '{') return false;
            stk.pop();
        }
        else if (c == ']') {
            if (stk.empty() || stk.top() != '[') return false;
            stk.pop();
        }
    }
    if (!stk.empty()) return false;
    return true;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s;
    while (1) {
        getline(cin, s);
        if (s == "#") break;
        if (legal(s)) cout << "Legal\n";
        else cout << "Illegal\n";
    }
    return 0;
}