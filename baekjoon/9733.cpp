#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int cnt[7];
int main()
{
    string s, Task[7] = { "Re","Pt","Cc","Ea","Tb","Cm","Ex" };
    int sum = 0;
    while (cin >> s) {
        loop(i, 7)
            if (s == Task[i]) {
                cnt[i]++;
                break;
            }
        sum += 1;
    }

    loop(i, 7) {
        cout << Task[i];
        printf(" %d %.2lf\n", cnt[i], (double)cnt[i] / sum);
    }
    printf("Total %d 1.00", sum);
    return 0;
}