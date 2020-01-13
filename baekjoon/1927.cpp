#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

int main()
{
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    int N, op;
    cin >> N;
    priority_queue<int, vector<int>, greater<int>>pq;
    while (N-- > 0) {
        cin >> op;
        if (op)
            pq.push(op);
        else {
            if (pq.size() == 0)
                cout << '0' << '\n';
            else {
                cout << pq.top() << '\n';
                pq.pop();
            }
        }
    }
    return 0;
}