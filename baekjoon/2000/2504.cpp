#include <iostream>
#include <stack>
using namespace std;

void calc(stack<int>& val, int k) {
    int ret = 0;
    while (val.top() != -1) {
        ret += val.top(); val.pop();
    }
    if (ret == 0) ret = 1;
    val.pop();
    val.push(ret * k);
}
int main() {
    stack<int> val;
    stack<char> stk;

    string s; cin >> s;
    for (char c : s) switch (c) {
    case '(':
    case '[':
        stk.push(c), val.push(-1);
        break;
    case ')':
        if (stk.empty() || stk.top() != '(') { cout << 0; return 0; }
        stk.pop();
        calc(val, 2); break;
    case ']':
        if (stk.empty() || stk.top() != '[') { cout << 0; return 0; }
        stk.pop();
        calc(val, 3); break;
    }

    if(!stk.empty()) { cout << 0; return 0; }

    int ans = 0;
    while (!val.empty()) {
        ans += val.top(); val.pop();
    }
    cout << ans;
    return 0;
}