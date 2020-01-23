#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

bool cake[1001];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int L, n, a, b, maxE = 0, maxR = 0, maxE_i, maxR_i;
    cin >> L >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a >> b;
        if (b - a > maxE) maxE = b - a, maxE_i = i;
        int sum = 0;
        for (int j = a; j <= b; ++j)
            if (!cake[j]) {
                ++sum;
                cake[j] = true;
            }
        if (sum > maxR) maxR = sum, maxR_i = i;
    }
    cout << maxE_i << '\n' << maxR_i;
    return 0;
}