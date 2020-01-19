#include <iostream>
#include <algorithm>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    int A[10], B[10];
    loop(i, 10) cin >> A[i];
    loop(i, 10) cin >> B[i];
    sort(A, A + 10), sort(B, B + 10);
    int a = 0, b = 0;
    for (int i = 9;i >= 7;--i)
        a += A[i], b += B[i];
    cout << a << ' ' << b;
    return 0;
}