#include <bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        priority_queue<int, vector<int>, greater<int>> pq_min;
        priority_queue<int> pq_max;
        vector<int> ans;
        int N; cin >> N;
        loop(i, N) {
            int x; cin >> x;
            if (pq_min.size() == pq_max.size())
                pq_max.push(x);
            else
                pq_min.push(x);
            if (!pq_max.empty() && !pq_min.empty() && pq_max.top() > pq_min.top()) {
                int a = pq_min.top(), b = pq_max.top();
                pq_min.pop(), pq_max.pop();
                pq_min.push(b), pq_max.push(a);
            }
            if (i % 2 == 0)
                ans.push_back(pq_max.top());
        }

        cout << ans.size() << '\n';
        loop(i, ans.size()) {
            cout << ans[i] << ' ';
            if ((i + 1) % 10 == 0 || i == ans.size() - 1) cout << '\n';
        }
    }
    return 0;
}