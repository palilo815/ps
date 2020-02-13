#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

const int max_N = 100000;

int arr[max_N + 1];

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    priority_queue<p, vector<p>, greater<p>> pq;

    int N; cin >> N;
    for (int i = 1; i <= N; ++i) {
        cin >> arr[i];
        pq.push({ arr[i],i });
    }

    int Q; cin >> Q;
    while (Q--) {
        int q; cin >> q;
        if (q == 1) {
            int i, v; cin >> i >> v;
            arr[i] = v;
            pq.push({ v,i });
        }
        else {
            while (arr[pq.top().second] != pq.top().first) pq.pop();
            cout << pq.top().second << '\n';
        }
    }
    return 0;
}