#include<bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int gcd(int a, int b)
{
    if (a == 0) return b;
    return gcd(b % a, a);
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string A, B; cin >> A >> B;
    int len_A = A.size(), len_B = B.size();
    int len = len_A * len_B / gcd(len_A, len_B);

    // 최소공배수만큼의 길이만 비교하면 된다.
    loop(i, len)
        if (A[i % len_A] != B[i % len_B]) {
            cout << 0;
            return 0;
        }
    cout << 1;
    return 0;
}