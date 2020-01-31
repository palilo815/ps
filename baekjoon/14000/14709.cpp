#include<bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    int n, Fg[3][2] = { 1,3,1,4,3,4 };
    bool flag[4] = {};
    cin >> n;
    while (n--) {
        int a, b; cin >> a >> b;
        if (a > b) swap(a, b);
        loop(i, 3) {
            if (a == Fg[i][0] && b == Fg[i][1]) {
                flag[i] = true;
                break;
            }
            if (i == 2) flag[3] = true;
        }
    }
    if (flag[0] && flag[1] && flag[2] && !flag[3])
        cout << "Wa-pa-pa-pa-pa-pa-pow!";
    else
        cout << "Woof-meow-tweet-squeek";
    return 0;
}