#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        double b, p;
        cin >> b >> p;
        double BPM = 60 * b / p;
        double BPM_min = BPM * (b - 1) / b, BPM_max = BPM * (b + 1) / b;
        cout << fixed << setprecision(4)
            << BPM_min << ' ' << BPM << ' ' << BPM_max << '\n';
    }
    return 0;
}