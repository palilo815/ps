#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 1000000;

bool A[max_N + 2];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    loop(i, N) cin >> A[i];

    int ans = 0;
    loop(i, N) if (A[i]) {
        ++ans;
        A[i + 1] = !A[i + 1];
        A[i + 2] = !A[i + 2];
    }
    cout << ans;
    return 0;
}