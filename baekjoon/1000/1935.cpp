#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int val[26];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    string s; cin >> s;
    loop(i, N) cin >> val[i];

    stack<double> stk;
    for (char c : s) {
        if ('A' <= c && c <= 'Z') stk.push(val[c - 'A']);
        else {
            double b = stk.top(); stk.pop();
            double a = stk.top(); stk.pop();
            if (c == '+') stk.push(a + b);
            else if (c == '-') stk.push(a - b);
            else if (c == '*') stk.push(a * b);
            else stk.push(a / b);
        }
    }
    cout << fixed << setprecision(2) << stk.top();
    return 0;
}