#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, x; cin >> N;
    priority_queue<int, vector<int>, greater<int>> pq;
    
    // pq에 먼저 N개를 넣음
    loop(i, N) {
        cin >> x; pq.push(x);
    }

    // pq.top() : N번째 큰 수
    loop(i, N) loop(j, N - 1) {
        cin >> x;
        if (x > pq.top()) {
            pq.pop();
            pq.push(x);
        }
    }
    cout << pq.top();
    return 0;
}