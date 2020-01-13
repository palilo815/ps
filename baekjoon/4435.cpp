#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int A[6] = { 1,2,3,3,4,10 }, B[7] = { 1,2,2,2,3,5,10 };
    string* ans, sA = "Good triumphs over Evil", sB = "Evil eradicates all trace of Good", sC = "No victor on this battle field";
    int T; cin >> T;
    loop(t, T) {
        int sumA = 0, sumB = 0, x;
        loop(i, 6) {
            cin >> x;
            sumA += x * A[i];
        }
        loop(i, 7) {
            cin >> x;
            sumB += x * B[i];
        }
        if (sumA > sumB) ans = &sA;
        else if (sumA < sumB) ans = &sB;
        else ans = &sC;
        cout << "Battle " << t + 1 << ": " << *ans << '\n';
    }
    return 0;
}