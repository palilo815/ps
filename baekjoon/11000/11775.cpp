#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int P, M;
stack<pair<int, int>> postfix;

bool is_digit(char c) { return '0' <= c && c <= '9'; }
void evaluate(char op) {
    auto [coef1, num1] = postfix.top(); postfix.pop();
    auto [coef2, num2] = postfix.top(); postfix.pop();
    switch (op) {
    case '+':
        postfix.emplace((coef1 + coef2) % M, (num1 + num2) % M);
        break;
    case '-':
        postfix.emplace((coef2 - coef1 + M) % M, (num2 - num1 + M) % M);
        break;
    case '*':
        postfix.emplace(((ll)coef1 * num2 + (ll)coef2 * num1) % M, (ll)num1 * num2 % M);
    }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    string s;
    cin >> s >> P >> M;

    stack<char> stk;
    int len = s.size();
    
    for (int i = 0; i < len; ++i) {
        if (is_digit(s[i])) {
            int val = s[i] - '0', j = i + 1;
            while (j < len && is_digit(s[j])) {
                val = (val * 10 + s[j] - '0') % M;
                ++j;
            }
            postfix.emplace(0, val);
            i = j - 1;
        }
        else switch (s[i]) {
        case '(': stk.emplace('(');
            break;
        case ')':
            while (!stk.empty() && stk.top() != '(')
                evaluate(stk.top()), stk.pop();
            stk.pop();
            break;
        case '+':
        case '-':
            while (!stk.empty() && stk.top() != '(')
                evaluate(stk.top()), stk.pop();
            stk.emplace(s[i]);
            break;
        case '*':
            while (!stk.empty() && stk.top() == '*')
                evaluate(stk.top()), stk.pop();
            stk.emplace('*');
            break;
        default: postfix.emplace(1, 0);
        }
    }
    while (!stk.empty())
        evaluate(stk.top()), stk.pop();

    auto [coef, num] = postfix.top();
    for (ll i = 1; ; ++i)
        if ((coef * i + num) % M == P) {
            cout << i;
            break;
        }
    return 0;
}