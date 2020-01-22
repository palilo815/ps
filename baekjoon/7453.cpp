#include<iostream>
#include<algorithm>
#define loop(i,n) for(int i=0;i<n;++i)
#define ll long long
#define max_N 4000
using namespace std;

int A[max_N], B[max_N], C[max_N], D[max_N];
int X[max_N * max_N], Y[max_N * max_N];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n; cin >> n;
    loop(i, n) cin >> A[i] >> B[i] >> C[i] >> D[i];
    loop(i, n) loop(j, n) X[i * n + j] = A[i] + B[j];
    loop(i, n) loop(j, n) Y[i * n + j] = C[i] + D[j];
    n *= n;
    sort(X, X + n);
    sort(Y, Y + n);
    ll ans = 0;
    loop(i, n) {
        int key = -X[i];
        auto low = lower_bound(Y, Y + n, key), up = upper_bound(Y, Y + n, key);
        if(low != up)
            ans += (up - low);
    }
    cout << ans;
    return 0;
}