#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    stack<int> stk;
    vector<char> ans;
    int i = 1;
    bool valid = true;
    int N; cin >> N;
    while (N--) {
        int x; cin >> x;
        if (x < i) {
            if (stk.top() == x) {
                stk.pop();
                ans.emplace_back('-');
            }
            else {
                valid = false;
                break;
            }
        }
        if (x > i) while (x != i) {
            stk.emplace(i++);
            ans.emplace_back('+');
        }
        if (x == i) {
            ++i;
            ans.emplace_back('+');
            ans.emplace_back('-');
        }
    }
    if (valid) for (char c : ans)
        cout << c << '\n';
    else cout << "NO";
    return 0;
}