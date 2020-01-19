#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

void Cantor(int len) {
    if (len == 1) cout << '-';
    else {
        Cantor(len / 3);
        cout << string(len / 3, ' ');
        Cantor(len / 3);
    }
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N;
    while (cin >> N) {
        Cantor(pow(3, N));
        cout << '\n';
    }
    return 0;
}