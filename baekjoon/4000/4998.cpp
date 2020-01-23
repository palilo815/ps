#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    double Money, itr, Goal;
    while (cin >> Money >> itr >> Goal) {
        int Ans = 0;
        double tmp = (100.0 + itr) / 100.0;
        while (Money < Goal) {
            Money *= tmp;
            ++Ans;
        }
        cout << Ans << '\n';
    }
    return 0;
}