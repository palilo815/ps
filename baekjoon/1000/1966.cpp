#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
int main()
{
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    int t, n, key, priority;
    cin >> t;
    while (t-- > 0) {
        cin >> n >> key;
        queue<pair<int, int>> que;
        priority_queue<int> pq;
        for (int i = 0; i < n;i++) {
            cin >> priority;
            que.push(make_pair(i, priority));
            pq.push(priority);
        }
        int ans = 0;
        while (1) {
            int a = que.front().first, b = que.front().second;
            if (pq.top() > b) {
                que.pop();
                que.push(make_pair(a, b));
            }
            else {
                que.pop();
                ans++;
                pq.pop();
                if (a == key) break;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}