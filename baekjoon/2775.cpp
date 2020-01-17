#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int flat[15][15];
int main()
{    
    loop(i, 15) flat[0][i] = i;
    for (int F = 1; F < 15; ++F) loop(room, 15) loop(i, room + 1)
        flat[F][room] += flat[F - 1][i];
    int T; cin >> T;
    while (T--) {
        int F, room; cin >> F >> room;
        cout << flat[F][room] << '\n';
    }
    return 0;
}