#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef long long ll;
const int max_N = 500000;

ll A[max_N], B[max_N];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    loop(i, N) cin >> A[i];
    loop(i, N) cin >> B[i];
    loop(i, N) cout << upper_bound(B + i + 1, B + N, A[i]) - (B + i + 1) << ' ';
    return 0;
}