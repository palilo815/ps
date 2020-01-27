#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int quad[5];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, x, y;
    cin >> n;
    while (n--) {
        cin >> x >> y;
        if (x == 0 || y == 0) quad[0]++;
        else if (x > 0) {
            if (y > 0) quad[1]++;
            else if (y < 0) quad[4]++;
        }
        else if (x < 0) {
            if (y > 0) quad[2]++;
            else if (y < 0) quad[3]++;
        }
    }
    for (int i = 1; i < 5; ++i)
        cout << 'Q' << i << ": " << quad[i] << '\n';
    cout << "AXIS: " << quad[0];
    return 0;
}