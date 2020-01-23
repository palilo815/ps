#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

bool tri_six(int n)
{
    int cnt = 0;;
    while (n) {
        if (n % 10 == 6) {
            if (++cnt == 3) return true;
        }
        else cnt = 0;
        n /= 10;
    }
    return false;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, i = 0, num = 666;
    cin >> N;
    while (1) {
        if (tri_six(num)) ++i;
        if (i == N) {
            cout << num;
            break;
        }
        ++num;
    }
    return 0;
}