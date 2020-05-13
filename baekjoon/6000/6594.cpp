#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

stack<p> num;
stack<char> op;

string s;

bool is_digit(char c) { return '0' <= c && c <= '9'; }
void evaluate(char c) {
    auto [coef2, num2] = num.top(); num.pop();
    auto [coef1, num1] = num.top(); num.pop();
    switch (c) {
    case '+':
        num.emplace(coef1 + coef2, num1 + num2);
        break;
    case '-':
        num.emplace(coef1 - coef2, num1 - num2);
        break;
    case '*':
        num.emplace(coef1 * num2 + coef2 * num1, num1 * num2);
    }
}
p solve(size_t l, size_t r) {
    while (l < r) {
        if (is_digit(s[l])) {
            int val = s[l] - '0', m = l + 1;
            while (m < r && is_digit(s[m])) {
                val = val * 10 + s[m] - '0';
                ++m;
            }
            num.emplace(0, val);
            l = m - 1;
        }
        else switch (s[l]) {
        case '(': op.emplace('('); break;
        case ')':
            while (!op.empty() && op.top() != '(')
                evaluate(op.top()), op.pop();
            op.pop();
            break;
        case '+':
        case '-':
            while (!op.empty() && op.top() != '(')
                evaluate(op.top()), op.pop();
            op.emplace(s[l]);
            break;
        case '*':
            while (!op.empty() && op.top() == '*')
                evaluate(op.top()), op.pop();
            op.emplace('*');
            break;
        default: num.emplace(1, 0);
        }
        ++l;
    }
    while (!op.empty())
        evaluate(op.top()), op.pop();

    p res = num.top(); num.pop();
    return res;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);


    int T = 0;
    while (cin >> s) {
        auto eq = s.find('=');
        auto [coef, num] = solve(0, eq);
        auto [coef2, num2] = solve(eq + 1, s.size());

        coef -= coef2, num2 -= num;
        cout << "Equation #" << ++T << '\n';
        if (coef == 0) {
            if (num2) cout << "No solution.";
            else cout << "Infinitely many solutions.";
        }
        else {
            double ans = 1.0 * num2 / coef;
            cout << "x = " << fixed << setprecision(6) << ans;
        }
        cout << '\n' << '\n';
    }
    return 0;
}