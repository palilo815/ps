#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int A[200000];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int a, b, IntS = 0;
    cin >> a >> b;
    loop(i, a) cin >> A[i];
    sort(A, A + a);
    loop(i, b) {
        int x; cin >> x;
        if (binary_search(A, A + a, x))
            ++IntS;
    }
    // A와 B의 원소의 개수에서 교집합 * 2를 뺀다.
    cout << a + b - 2 * IntS;
    return 0;
}