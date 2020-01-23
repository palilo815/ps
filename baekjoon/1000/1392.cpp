#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int song[10000];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, Q; cin >> N >> Q;
    int idx = 0;
    loop(i, N) {
        int t; cin >> t;
        while (t--) song[idx++] = i + 1;
    }
    while (Q--) {
        int t; cin >> t;
        cout << song[t] << '\n';
    }
    return 0;
}