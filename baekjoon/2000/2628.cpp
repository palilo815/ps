#include <bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

bool ver[101], hor[101];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int h, w; cin >> w >> h;
    hor[h] = true, ver[w] = true;
    int N; cin >> N;
    loop(i, N) {
        int d, pos; cin >> d >> pos;
        if (d) ver[pos] = true;
        else hor[pos] = true;
    }
    int curr = 0, max_h = 0, max_w = 0;
    loop(i, h + 1)
        if (hor[i]) {
            max_h = max(max_h, i - curr);
            curr = i;
        }
    curr = 0;
    loop(i, w + 1)
        if (ver[i]) {
            max_w = max(max_w, i - curr);
            curr = i;
        }
    cout << max_h * max_w;
    return 0;
}