#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    int n, A[20], B[20];
    while (1) {
        cin >> n;
        if (n == 0) break;
        int pa = 0, pb = 0;
        loop(i, n) cin >> A[i];
        loop(i, n) cin >> B[i];
        loop(i, n) {
            int a = A[i], b = B[i];
            if (a > b) {
                if (a > b + 1) pa += a;
                else if (b > 1) pb += (a + b);
                else pb += 6;
            }
            else if (a < b) {
                if (a + 1 < b) pb += b;
                else if (a > 1) pa += (a + b);
                else pa += 6;
            }
        }
        printf("A has %d points. B has %d points.\n\n", pa, pb);
    }
    return 0;
}