#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int t, n, vote[10];
    cin >> t;
    while (t--) {
        cin >> n;
        int sum = 0, max_v = 0;
        bool dup = false;
        loop(i, n) {
            int V; cin >> V;
            vote[i] = V;
            sum += V;
            if (V > max_v) { max_v = V; dup = false; }
            else if (max_v == V) dup = true;
        }
        if (dup) cout << "no winner\n";
        else {
            int win;
            loop(i, n) if (vote[i] == max_v) { win = i + 1; break; }
            if (max_v > sum / 2) cout << "majority ";
            else cout << "minority ";
            cout << "winner " << win << '\n';
        }
    }
    return 0;
}