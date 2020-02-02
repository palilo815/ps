#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int A[101], B[65];
int money_A[7] = { 0,500,300,200,50,30,10 }, money_B[6] = { 0,512,256,128,64,32 };

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int index = 1;
    for (int i = 1; i <= 6; ++i)
        loop(j, i)
        A[index++] = money_A[i];
    index = 1;
    for (int i = 1; i <= 5; ++i)
        loop(j, 1 << (i - 1))
        B[index++] = money_B[i];

    int T, a, b;
    cin >> T;
    while (T--) {
        cin >> a >> b;
        cout << (A[a] + B[b]) * 10000 << '\n';
    }
    return 0;
}