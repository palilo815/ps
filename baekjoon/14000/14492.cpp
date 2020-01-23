#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

bool A[300][300], B[300][300];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    loop(i, N) loop(j, N) cin >> A[i][j];
    loop(i, N) loop(j, N) cin >> B[i][j];

    int ans = 0;
    loop(i, N) loop(j, N) {
        bool tmp = false;
        int pos = 0;
        while (!tmp && pos < N) {
            tmp |= A[i][pos] & B[pos][j];
            ++pos;
        }
        if (tmp) ++ans;
    }
    cout << ans;
    return 0;
}