#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main() {
    int n; cin >> n;
    loop(i, n)
        cout << string(i, ' ') << string(n - i, '*') << '\n';
    return 0;
}