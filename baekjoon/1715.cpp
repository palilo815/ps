#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int main()
{
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    priority_queue<int, vector<int>, greater<int> > pq;
    int n, x, sum = 0;
    cin >> n;
    while (n-- > 0) {
        cin >> x;
        pq.push(x);
    }
    while (pq.size() != 1) {
        int a = pq.top();
        pq.pop();
        int b = pq.top();
        pq.pop();
        sum += (a + b);
        pq.push(a + b);
    }
    cout << sum;
    return 0;
}