#include <bits/stdc++.h>
using namespace std;

int main()
{
    stack<char> stk;
    string s; cin >> s;
    for (char x : s) switch (x) {
    case '(':
        // 무조건 넣는다.
        stk.push(x);
        break;
    case ')':
        // '('가 나올때까지 뽑아서 출력한다.
        // 스택 안의 연산자 중에서 ()로 묶인 부분의 우선순위가 제일 높기 때문.
        while (!stk.empty() && stk.top() != '(')
            cout << stk.top(), stk.pop();
        stk.pop();
        break;
    case '+':
    case '-':
        // 스택 안에 *,/,+,-연산이 있을 경우 먼저 해주고,
        // 자신을 스택에 넣는다.
        while (!stk.empty() && stk.top() != '(')
            cout << stk.top(), stk.pop();
        stk.push(x);
        break;
    case '*':
    case '/':
        // 스택 안에 *,/연산이 있을 경우 먼저 해주고,
        // 자신을 스택에 넣는다.
        while (!stk.empty() && (stk.top() == '*' || stk.top() == '/'))
            cout << stk.top(), stk.pop();
        stk.push(x);
        break;
        // 상수는 바로 출력
    default: cout << x;
    }
    while (!stk.empty())
        cout << stk.top(), stk.pop();
    return 0;
}