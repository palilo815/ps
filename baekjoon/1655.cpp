#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int main()
{
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    priority_queue<int, vector<int>, greater<int> > pq_min;
    priority_queue<int> pq_max;
    int n, x;
    cin >> n;
    while (n-- > 0) {
        cin >> x;
        if (pq_min.size() == pq_max.size())
            pq_max.push(x);
        else
            pq_min.push(x);
        if (!pq_min.empty() && !pq_max.empty() && pq_min.top() < pq_max.top()) {
            int a = pq_min.top(), b = pq_max.top();
            pq_min.pop(), pq_max.pop();
            pq_min.push(b), pq_max.push(a);
        }
        cout << pq_max.top() << '\n';
    }
    return 0;
}