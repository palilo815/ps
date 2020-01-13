#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

double score[1000];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        int N; cin >> N;
        double avg = 0;
        loop(i, N) {
            cin >> score[i];
            avg += score[i];
        }
        avg /= N;

        int cnt = 0;
        loop(i, N)
            if (score[i] > avg) ++cnt;

        cout << fixed << setprecision(3) << 100.0 * cnt / N << "%\n";
    }
    return 0;
}