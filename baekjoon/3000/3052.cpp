#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

bool check[42];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N = 10;
    while (N--) {
        int num; cin >> num;
        check[num % 42] = true;
    }

    int cnt = 0;
    loop(i, 42)
        if (check[i])
            ++cnt;
    cout << cnt;
    return 0;
}