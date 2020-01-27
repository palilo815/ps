#include <iostream>
#include <queue>
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, num;
    string order;
    queue<int> q;
    cin >> n;
    while (n--) {
        cin >> order;
        if (order == "push") {
            cin >> num;
            q.push(num);
        }
        else if (order == "pop") {
            if (q.empty()) cout << "-1\n";
            else {
                cout << q.front() << '\n';
                q.pop();
            }
        }
        else if (order == "size")
            cout << q.size() << '\n';
        else if (order == "empty")
            cout << q.empty() << '\n';
        else if (order == "front") {
            if (q.empty()) cout << "-1\n";
            else cout << q.front() << '\n';
        }
        else {
            if (q.empty()) cout << "-1\n";
            else cout << q.back() << '\n';
        }
    }
    return 0;
}