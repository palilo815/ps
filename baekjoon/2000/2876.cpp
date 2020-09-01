#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mxN = 1e5;

int dp[6];
bool grade[6];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    int mx_cnt = 0, mx_grade = 0;

    for (int i, j; N; --N) {
        cin >> i >> j;

        memset(grade + 1, 0, 5);
        grade[i] = grade[j] = true;

        for (int k = 1; k <= 5; ++k)
            if (grade[k]) ++dp[k];
            else {
                if (dp[k] > mx_cnt) {
                    mx_cnt = dp[k];
                    mx_grade = k;
                }
                dp[k] = 0;
            }
    }

    for (int k = 1; k <= 5; ++k)
        if (dp[k] > mx_cnt) {
            mx_cnt = dp[k];
            mx_grade = k;
        }

    cout << mx_cnt << ' ' << mx_grade;
    return 0;
}