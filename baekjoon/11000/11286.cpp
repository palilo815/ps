#include <bits/stdc++.h>
using namespace std;

auto cmp = [](int a, int b) {
    if (abs(a) == abs(b)) return a > b;
    return abs(a) > abs(b);
};
int main()
{
    priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);
    int N, x;
    scanf("%d", &N);
    while (N--) {
        scanf("%d", &x);
        if (x) pq.push(x);
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