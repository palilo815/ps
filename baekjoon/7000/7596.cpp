#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
const int max_N = 200;

string music[max_N];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, t = 0;
    while(1) {
        cin >> n;
        if (n == 0) break;
        cin.ignore();
        loop(i, n) getline(cin, music[i]);
        sort(music, music + n);
        cout << ++t << '\n';
        loop(i, n) cout << music[i] << '\n';
    }
    return 0;
}