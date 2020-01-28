#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
const int max_N = 1000000;

int A[max_N], B[max_N];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, m; cin >> n >> m;
    loop(i, n) cin >> A[i];
    loop(i, m) cin >> B[i];
    int i = 0, j = 0;
    while (i < n && j < m) {
        if (A[i] < B[j]) cout << A[i++] << ' ';
        else cout << B[j++] << ' ';
    }
    while (i < n) cout << A[i++] << ' ';
    while (j < m) cout << B[j++] << ' ';
    return 0;
}