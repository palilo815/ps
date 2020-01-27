#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

// DP : c원으로 만들 수 있는 최대 메모리
// max_N = 100, max_C = 100이므로, 최대 10000원이 사용될 수 있다.
int DP[10001], memory[100];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, m, c;
    cin >> n >> m;
    loop(i, n) cin >> memory[i];
    loop(i, n) {
        cin >> c;
        for (int j = 10000 - c; j >= 0; --j)
            if (DP[j])
                DP[j + c] = max(DP[j + c], DP[j] + memory[i]);
        DP[c] = max(DP[c], DP[0] + memory[i]);
    }
    loop(i, 10001)
        if (DP[i] >= m) {
            cout << i;
            break;
        }
    return 0;
}