#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> p;

const int max_N = 500;

int row[max_N];
int mat[max_N][max_N];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    loop(i, N) cin >> row[i];

    vector<p> col(N);
    loop(i, N) {
        cin >> col[i].first;
        col[i].second = i;
    }

    sort(col.begin(), col.end(), greater<p>());
    while (!col.empty() && col.back().first == 0)
        col.pop_back();

    loop(r, N) {
        if (col.size() < row[r]) { cout << -1; return 0; }

        loop(j, row[r]) {
            auto& [cnt, c] = col[j];
            --cnt;
            mat[r][c] = 1;
        }

        sort(col.begin(), col.end(), greater<p>());
        while (!col.empty() && col.back().first == 0)
            col.pop_back();
    }

    if (!col.empty()) { cout << -1; return 0; }
    cout << 1;
    loop(i, N) {
        cout << '\n';
        loop(j, N) cout << mat[i][j];
    }
    return 0;
}