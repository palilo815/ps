#include <iostream>
#include <stack>
using namespace std;

int main()
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    string s;
    int T; cin >> T;
    while (T--) {
        cin >> s;
        stack<char> stk;
        for (char c : s) {
            if (c == '(')
                stk.push(c);
            else {
                if (stk.empty()) {
                    stk.push(0);
                    break;
                }
                stk.pop();
            }
        }
        if (stk.empty()) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}