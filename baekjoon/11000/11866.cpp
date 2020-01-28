#include <bits/stdc++.h>
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, k, x;
    cin >> n >> k;
    queue<int> q;
    for (int i = 1; i <= n;i++)
        q.push(i);

    cout << '<';
    while (1) {
        for (int i = 0; i < k - 1; i++) {
            x = q.front(); q.pop();
            q.push(x);
        }
        cout << q.front(); q.pop();
        if (!q.empty()) cout << ", ";
        else {
            cout << '>';
            break;
        }
    }
    return 0;
}