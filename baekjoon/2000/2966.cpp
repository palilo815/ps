#include <bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    char Adrian[3] = { 'A', 'B', 'C' }, Bruno[4] = { 'B', 'A', 'B', 'C' }, Goran[6] = { 'C','C','A','A','B','B' };
    int n, A = 0, B = 0, G = 0;
    cin >> n;
    loop(i, n) {
        char c; cin >> c;
        A += (c == Adrian[i % 3]);
        B += (c == Bruno[i % 4]);
        G += (c == Goran[i % 6]);
    }

    int Max = max(A, B);
    Max = max(Max, G);
    cout << Max << '\n';

    if (Max == A) cout << "Adrian" << '\n';
    if (Max == B) cout << "Bruno" << '\n';
    if (Max == G) cout << "Goran" << '\n';
    return 0;
}