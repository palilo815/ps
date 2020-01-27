#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

struct MatSal {
    int w;
    int c;
};

MatSal choice(MatSal& a, MatSal& b)
{
    int A = a.w * b.c, B = a.c * b.w;
    if (A > B) return a;
    if (A < B) return b;
    if (a.c < b.c) return a;
    else return b;
}

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T, N;
    cin >> T;
    while (T--) {
        cin >> N;
        MatSal buy;
        buy.w = 1, buy.c = 100000;
        while (N--) {
            MatSal tmp;
            cin >> tmp.w >> tmp.c;
            buy = choice(buy, tmp);
        }
        cout << buy.c << '\n';
    }
    return 0;
}