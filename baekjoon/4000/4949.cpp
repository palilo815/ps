#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    string s;
    while (1) {
        getline(cin, s);
        if (s == ".") break;

        int invalid = 0;
        stack<char> stk;
        for (char c : s) {
            if (c == '(' || c == '[')
                stk.push(c);
            else if (c == ')') {
                if (stk.empty() || stk.top() != '(') {
                    invalid = 1;
                    break;
                }
                stk.pop();
            }
            else if (c == ']') {
                if (stk.empty() || stk.top() != '[') {
                    invalid = 1;
                    break;
                }
                stk.pop();
            }
        }
        if (!stk.empty()) invalid = 1;

        cout << (invalid ? "no" : "yes") << '\n';
    }
    return 0;
}