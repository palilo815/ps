#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
int main()
{
    string A, B; cin >> A >> B;
    loop(i, A.size())
        if (A[i] == '6')
            A[i] = '5';
    loop(i, B.size())
        if (B[i] == '6')
            B[i] = '5';
    int min_val = stoi(A) + stoi(B);
    loop(i, A.size())
        if (A[i] == '5')
            A[i] = '6';
    loop(i, B.size())
        if (B[i] == '5')
            B[i] = '6';
    int max_val = stoi(A) + stoi(B);
    cout << min_val << " " << max_val;
    return 0;
}