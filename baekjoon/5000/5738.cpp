#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    char res[2] = { 'N','Y' };
    int A[11], D[11], a, d;
    while (1) {
        cin >> a >> d;
        if (a == 0 && d == 0) break;
        loop(i, a) cin >> A[i];
        loop(i, d) cin >> D[i];
        sort(A, A + a), sort(D, D + d);
        cout << res[A[0] < D[1]] << '\n';
    }
    return 0;
}