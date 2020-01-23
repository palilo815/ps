#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int a[10], b[10]; // A와 B의 카드
    loop(i, 10) cin >> a[i];
    loop(i, 10) cin >> b[i];

    // A와 B의 점수, 마지막에 누가 이겼는지.
    int A = 0, B = 0, last = 0;
    loop(i, 10) {
        if (a[i] > b[i]) A += 3, last = 1;
        else if (a[i] < b[i]) B += 3, last = 2;
        else ++A, ++B;
    }
    cout << A << ' ' << B << '\n';
    if (A > B) cout << 'A';
    else if (A < B) cout << 'B';
    else {
        if (last == 1) cout << 'A';
        else if (last == 2) cout << 'B';
        else cout << 'D';
    }
    return 0;
}