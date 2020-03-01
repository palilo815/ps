#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 1000;

int cls[max_N][5];
bool check[max_N];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    loop(i, N) loop(j, 5) cin >> cls[i][j];
    int idx = -1, max_vote = -1;
    loop(i, N) {
        memset(check, 0, N);
        loop(j, N) loop(k, 5) if (cls[i][k] == cls[j][k]) check[j] = true;
        int vote = 0;
        loop(j, N) if (check[j]) ++vote;
        if (vote > max_vote) {
            max_vote = vote;
            idx = i;
        }
    }
    cout << idx + 1;
    return 0;
}