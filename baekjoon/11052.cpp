#include <iostream>
#include <algorithm>
#define max_N 1000
using namespace std;

// i장을 사는데 드는 최댓값
int DP[max_N + 1];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);
    
    int N, cost; cin >> N;

    // basis : DP[0] = 0, 0장의 카드를 사는 데에 0원이 든다.

    for (int i = 1;i <= N;++i) {
        // i장의 카드를 cost에 살 수 있다.
        cin >> cost;
        for (int j = i;j <= N;++j)
            DP[j] = max(DP[j], DP[j - i] + cost);
    }
    cout << DP[N];
    return 0;
}