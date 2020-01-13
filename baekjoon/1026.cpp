#include <bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, sum = 0;
    cin >> N;
    vector<int> A(N), B(N);
    loop(i, N) cin >> A[i];
    loop(i, N) cin >> B[i];
    sort(A, A + N);
    sort(B, B + N, greater<int>());
    loop(i, N) sum += A[i] * B[i];
    cout << sum;
    return 0;
}