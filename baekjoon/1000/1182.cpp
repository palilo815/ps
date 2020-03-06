#include <iostream>
using namespace std;

int ans, N, S;
int arr[20];

void solve(int i, int sum) {
    if (i == N) {
        if (sum == S) ++ans;
        return;
    }
    solve(i + 1, sum);
    solve(i + 1, sum + arr[i]);
}
int main() {
    cin >> N >> S;
    for (int i = 0; i < N; ++i) cin >> arr[i];
    solve(0, 0);
    if (S == 0) --ans;
    cout << ans;
    return 0;
}