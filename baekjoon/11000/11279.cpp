#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N, op;
    scanf("%d", &N);
    priority_queue<int> pq;
    while (N--) {
        scanf("%d", &op);
        if (op) pq.push(op);
        else {
            if (pq.empty()) printf("0\n");
            else {
                printf("%d\n", pq.top());
                pq.pop();
            }
        }
    }
    return 0;
}