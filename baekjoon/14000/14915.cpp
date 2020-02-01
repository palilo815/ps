#include <bits/stdc++.h>
using namespace std;

int main()
{
    int num, dec;
    cin >> num >> dec;
    if (num == 0) {
        cout << 0;
        return 0;
    }

    stack<char> stk;
    while (num) {
        int x = num % dec;
        num /= dec;
        if (x > 9) stk.push(x - 10 + 'A');
        else stk.push(x + '0');
    }
    while (!stk.empty()) {
        cout << stk.top();
        stk.pop();
    }
    return 0;
}