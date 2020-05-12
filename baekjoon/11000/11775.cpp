#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int P, M;
string s;
vector<pair<int, char>> postfix;

bool is_digit(char c) {
    return '0' <= c && c <= '9';
}
void make_postfix() {
    stack<char> stk;
    int len = s.size();
    for (int i = 0; i < len; ++i) {
        if (is_digit(s[i])) {
            int val = 0, j = i;
            while (j < len && is_digit(s[j])) {
                val = (val * 10 + s[j] - '0') % M;
                ++j;
            }
            postfix.emplace_back(val, 0);
            i = j - 1;
        }
        else switch (s[i]) {
        case '(': stk.emplace('('); break;
        case ')':
            while (!stk.empty() && stk.top() != '(') {
                postfix.emplace_back(0, stk.top());
                stk.pop();
            }
            stk.pop();
            break;
        case '+':
        case '-':
            while (!stk.empty() && stk.top() != '(') {
                postfix.emplace_back(0, stk.top());
                stk.pop();
            }
            stk.emplace(s[i]);
            break;
        case '*':
            while (!stk.empty() && stk.top() == '*') {
                postfix.emplace_back(0, stk.top());
                stk.pop();
            }
            stk.emplace('*');
            break;
        default: postfix.emplace_back(0, 'x');
        }
    }
    while (!stk.empty()) {
        postfix.emplace_back(0, stk.top());
        stk.pop();
    }
}
pair<int, int> calc() {
    stack<pair<int, int>> stk;
    for (auto [n, op] : postfix) {
        if (!op) stk.emplace(0, n);
        else if (op == 'x') stk.emplace(1, 0);
        else {
            auto [coef1, num1] = stk.top(); stk.pop();
            auto [coef2, num2] = stk.top(); stk.pop();
            switch (op) {
            case '+':
                stk.emplace((coef1 + coef2) % M, (num1 + num2) % M);
                break;
            case '-':
                stk.emplace((coef2 - coef1 + M) % M, (num2 - num1 + M) % M);
                break;
            case '*':
                stk.emplace(((ll)coef1 * num2 + (ll)coef2 * num1) % M, (ll)num1 * num2 % M);
            }
        }
    }
    return stk.top();
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> s >> P >> M;
    make_postfix();

    auto [coef, num] = calc();
    for (ll i = 1; ; ++i)
        if (((coef * i + num) % M + M) % M == P) {
            cout << i;
            break;
        }
    return 0;
}