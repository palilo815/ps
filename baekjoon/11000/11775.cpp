#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int mxN = 1e5;

int P, M;
char s[mxN + 1];
stack<pair<int, int>> num;
stack<char> op;

inline bool is_digit(char c) { return '0' <= c && c <= '9'; }
void evaluate() {
    auto [coef1, num1] = num.top();
    num.pop();
    auto [coef2, num2] = num.top();
    num.pop();
    switch (op.top()) {
    case '+': num.emplace((coef1 + coef2) % M, (num1 + num2) % M); break;
    case '-': num.emplace((coef2 - coef1 + M) % M, (num2 - num1 + M) % M); break;
    default: num.emplace(((ll)coef1 * num2 + (ll)coef2 * num1) % M, (ll)num1 * num2 % M);
    }
    op.pop();
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    cin >> s >> P >> M;
    for (int i = 0; s[i]; ++i) {
        if (is_digit(s[i])) {
            int val = (s[i] - '0') % M, j = i + 1;
            for (; s[j] && is_digit(s[j]); ++j)
                val = (val * 10 + s[j] - '0') % M;
            num.emplace(0, val);
            i = j - 1;
        } else
            switch (s[i]) {
            case '(': op.emplace('('); break;
            case ')':
                while (!op.empty() && op.top() != '(') evaluate();
                op.pop();
                break;
            case '+':
            case '-':
                while (!op.empty() && op.top() != '(') evaluate();
                op.emplace(s[i]);
                break;
            case '*':
                while (!op.empty() && op.top() == '*') evaluate();
                op.emplace('*');
                break;
            default: num.emplace(1, 0);
            }
    }
    while (!op.empty())
        evaluate();

    auto [c, n] = num.top();
    for (ll i = 0;; ++i)
        if ((c * i + n) % M == P)
            return cout << i, 0;
}