#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

char A[13] = { 'A','2','3','4','5','6','7','8','9','T','J','Q','K' };
int B[13];
int main()
{
    string card;
    loop(i, 5) {
        cin >> card;
        loop(i, 13)
            if (A[i] == card[0]) ++B[i];
    }
    
    int ans = 0;
    loop(i, 13)
        if (B[i] > ans) ans = B[i];
    cout << ans;
    return 0;
}