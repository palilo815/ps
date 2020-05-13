#include <bits/stdc++.h>
using namespace std;

stack<int> num;
stack<char> op;

bool is_digit(char c) {
    return '0' <= c && c <= '9';
}
void evaluate(char c) {
    int B = num.top(); num.pop();
    int A = num.top(); num.pop();
    switch (c) {
    case '+': num.emplace(A + B); break;
    case '-': num.emplace(A - B); break;
    case '<': num.emplace(min(A, B)); break;
    case '>': num.emplace(max(A, B));
    }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    string s; cin >> s;
    size_t len = s.size();
    for (size_t i = 0; i < len; ++i) {
        if (is_digit(s[i])) {
            int val = s[i] - '0';
            auto j = i + 1;
            while (j < len && is_digit(s[j])) {
                val = val * 10 + s[j] - '0';
                ++j;
            }
            num.emplace(val);
            i = j - 1;
        }
        else switch (s[i]) {
        case '+':
        case '-':
            while (!op.empty() && op.top() != '(')
                evaluate(op.top()), op.pop();
            op.emplace(s[i]);
            break;
        case '<':
        case '>':
            while (!op.empty() && (op.top() == '<' || op.top() == '>'))
                evaluate(op.top()), op.pop();
            op.emplace(s[i]);
            ++i;
            break;
        case '(': op.emplace('('); break;
        case ')':
            while (!op.empty() && op.top() != '(')
                evaluate(op.top()), op.pop();
            op.pop();
        }
    }
    while (!op.empty())
        evaluate(op.top()), op.pop();
    cout << num.top();
    return 0;
}