#include<bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int T[100];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n; cin >> n;
    loop(i, n) cin >> T[i];
    sort(T, T + n);

    int a, b;
    a = n / 2 - 1;
    b = n / 2 + (n % 2);
    if (n % 2) {
        cout << T[n / 2];
        while (a >= 0) cout << ' ' << T[b++] << ' ' << T[a--];
    }
    else
        while (a >= 0) cout << T[a--] << ' ' << T[b++] << ' ';
    return 0;
}