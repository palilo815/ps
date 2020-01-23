#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define P pair<int,int>
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    // 숫자와 index를 넣는다.
    // pq.top().first : 최솟값
    priority_queue<P, vector<P>, greater<P>> pq;
    int N, L; cin >> N >> L;
    loop(i, N) {
        int x; cin >> x;
        pq.push({ x,i });
        // 구하고자 하는 범위 밖의 수를 다 뺀다.
        while (pq.top().second <= i - L) pq.pop();
        cout << pq.top().first << ' ';
    }
    return 0;
}