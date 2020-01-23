#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, two = 0, five = 0;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        int tmp = i;
        while (tmp % 2 == 0)
            tmp /= 2, ++two;
        while (tmp % 5 == 0)
            tmp /= 5, ++five;
    }
    // n!를 소인수분해 했을 때 
    // two : 2의 개수, five : 5의 개수
    cout << min(two, five);
    return 0;
}