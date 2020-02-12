#include <bits/stdc++.h>
using namespace std;
const int max_N = 50000;

int DP[max_N + 1];

int main()
{
    int N; cin >> N;
    for (int i = 1; i <= N; ++i) DP[i] = INT_MAX;
    for (int i = 1; i * i <= N; ++i) {
        int sqr = i * i;
        for (int num = 0; num + sqr <= N; ++num)
            if (DP[num] != INT_MAX)
                DP[num + sqr] = min(DP[num + sqr], DP[num] + 1);
    }
    cout << DP[N];
    return 0;
}