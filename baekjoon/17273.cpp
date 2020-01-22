#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int card[2];
    int n, m, side = 0;
    cin >> n >> m;
    loop(i, 2) cin >> card[i];
    while (m--) {
        int x; cin >> x;
        if (card[side] <= x) side = 1 - side;
    }
    cout << card[side];
    return 0;
}