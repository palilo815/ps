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
        if (s == ".") break;

        bool balanced = true;
        stack<char> stk;
        loop(i, s.size()) {
            // 왼쪽 괄호를 stack에 넣음
            if (s[i] == '(' || s[i] == '[')
                stk.push(s[i]);

            // 오른쪽 괄호가 나오면, stack 위에 짝이 맞는 괄호가 있어야 한다.
            else if (s[i] == ')') {
                if (stk.empty() || stk.top() != '(') {
                    balanced = false;
                    break;
                }
                stk.pop();
            }
            else if (s[i] == ']') {
                if (stk.empty() || stk.top() != '[') {
                    balanced = false;
                    break;
                }
                stk.pop();
            }
        }
        // 왼쪽 괄호가 남아있을 경우 false
        if (!stk.empty()) balanced = false;

        if (balanced) cout << "yes\n";
        else cout << "no\n";
    }
    return 0;
}