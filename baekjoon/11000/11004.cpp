#include <iostream>
#include <queue>
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    priority_queue<int> pq;
    int n, k, x; cin >> n >> k;

    // k개는 그냥 넣고
    // n-k개는 비교하면서 넣는다.
    n -= k;
    while (k--) {
        cin >> x;
        pq.push(x);
    }
    while (n--) {
        cin >> x;
        if (x <= pq.top()) {
            pq.pop();
            pq.push(x);
        }
    }
    cout << pq.top();
    return 0;
}