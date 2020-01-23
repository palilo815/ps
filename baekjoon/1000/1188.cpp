#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M; cin >> N >> M;
    cout << M - gcd(N, M);
    return 0;
}