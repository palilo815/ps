#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    // 배열 9개면 차고 넘친다.
    // U, D : 최댓값, 최솟값
    int U[3], D[3], tmp[3];
    int n; cin >> n;
    
    // basis
    loop(i, 3) {
        int x; cin >> x;
        U[i] = D[i] = x;
    }

    for (int i = 1; i < n; ++i) {
        loop(j, 3) cin >> tmp[j];

        int a = max(U[0], U[1]);
        int b = max(U[1], U[2]);
        U[0] = a + tmp[0], U[1] = max(a, b) + tmp[1], U[2] = b + tmp[2];

        a = min(D[0], D[1]);
        b = min(D[1], D[2]);
        D[0] = a + tmp[0], D[1] = min(a, b) + tmp[1], D[2] = b + tmp[2];
    }
    sort(U, U + 3), sort(D, D + 3);
    cout << U[2] << ' ' << D[0];
    return 0;
}