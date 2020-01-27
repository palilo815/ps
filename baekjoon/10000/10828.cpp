#include <iostream>
#include <stack>
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, num;
    string order;
    stack<int> stk;
    cin >> n;
    while (n--) {
        cin >> order;
        if (order == "push") {
            cin >> num;
            stk.push(num);
        }
        else if (order == "pop") {
            if (stk.size() == 0) cout << "-1\n";
            else {
                cout << stk.top() << '\n';
                stk.pop();
            }
        }
        else if (order == "size")
            cout << stk.size() << '\n';
        else if (order == "empty")
            cout << stk.empty() << '\n';
        else {
            if (stk.size() == 0) cout << "-1\n";
            else cout << stk.top() << '\n';
        }
    }
    return 0;
}