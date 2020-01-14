#include<bits/stdc++.h>
using namespace std;
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    queue<int> q;
    int n;  cin >> n;
    for (int i = 1; i <= n; i++) q.push(i);
    while (q.size() != 1) {
        cout << q.front() << ' ';
        q.pop();
        int x = q.front();
        q.pop();
        q.push(x);
    }
    cout << q.front();
    return 0;
}