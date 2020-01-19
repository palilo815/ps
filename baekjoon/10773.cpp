#include <iostream>
#include <stack>
using namespace std;

int main()
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    stack<int> stk;
    int T, n;
    cin >> T;
    while (T--) {
        cin >> n;
        if (n == 0) stk.pop();
        else stk.push(n);
    }
    int sum = 0;
    while (!stk.empty()) {
        sum += stk.top();
        stk.pop();
    }
    cout << sum;
    return 0;
}