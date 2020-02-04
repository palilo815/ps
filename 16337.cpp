#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int ans[7][2];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    ans[1][0] = 1 << 4;

    ans[2][0] = 1 + (1 << 8);
    ans[2][1] = (1 << 2) + (1 << 6);

    ans[3][0] = ans[2][0] + (1 << 4);
    ans[3][1] = ans[2][1] + (1 << 4);

    ans[4][0] = 1 + (1 << 2) + (1 << 6) + (1 << 8);

    ans[5][0] = ans[4][0] + (1 << 4);

    ans[6][0] = (1 << 9) - 1 - (1 << 3) - (1 << 4) - (1 << 5);
    ans[6][1] = (1 << 9) - 1 - (1 << 1) - (1 << 4) - (1 << 7);

    int dice_mask = 0;
    loop(i, 9) {
        char c; cin >> c;
        if (c == 'o')
            dice_mask += (1 << i);
    }
    
    int eye = __builtin_popcount(dice_mask);
    bool unknown = true;
    if (dice_mask == ans[eye][0] || dice_mask == ans[eye][1])
        cout << eye;
    else cout << "unknown";
    return 0;
}