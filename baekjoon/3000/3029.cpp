#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T[2][3];
    loop(i, 2) {
        char c; // ':' 처리용
        cin >> T[i][0] >> c >> T[i][1] >> c >> T[i][2];
    }

    T[1][2] -= T[0][2];
    if (T[1][2] < 0) --T[1][1], T[1][2] += 60;
    T[1][1] -= T[0][1];
    if (T[1][1] < 0) --T[1][0], T[1][1] += 60;
    T[1][0] -= T[0][0];
    if (T[1][0] < 0) T[1][0] += 24;
    if (T[1][0] == 0 && T[1][1] == 0 && T[1][2] == 0) T[1][0] = 24;
    loop(i, 3) {
        cout << setfill('0') << setw(2) << T[1][i];
        if (i != 2) cout << ':';
    }
    return 0;
}