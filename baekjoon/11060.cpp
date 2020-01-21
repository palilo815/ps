#include <iostream>
#include <algorithm>
#define loop(i,n) for(int i=0;i<n;++i)
#define max_N 1000
using namespace std;

int jump[max_N], DP[max_N];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    loop(i, N) cin >> jump[i];

    loop(i, N) DP[i] = max_N;
    DP[0] = 0;

    loop(i, N)
        for (int j = i + 1;j <= i + jump[i];++j)
            DP[j] = min(DP[j], DP[i] + 1);

    if (DP[N - 1] == max_N) DP[N - 1] = -1;
    cout << DP[N - 1];
    return 0;
}