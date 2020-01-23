#include<iostream>
#include<stack>
#include<queue>
using namespace std;

int main()
{
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    int n, x, i = 1;
    stack<int> stk;
    queue<char> ans;
    bool flag = true;
    cin >> n;
    while (n-- > 0) {
        cin >> x;
        if (x < i) {
            if (stk.top() == x) {
                stk.pop();
                ans.push('-');
            }
            else {
                flag = false;
                while (n-- >= 0) cin.ignore();
            }
        }
        if (x > i) {
            while (x != i) {
                stk.push(i++);
                ans.push('+');
            }
        }
        if (x == i) {
            i++;
            ans.push('+');
            ans.push('-');
        }
    }
    if (flag) {
        while (!ans.empty()) {
            cout << ans.front() << '\n';
            ans.pop();
        }
    }
    else cout << "NO";
    return 0;
}