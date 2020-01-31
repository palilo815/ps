#include <iostream>
using namespace std;

void solve(int num) {
    int tmp = 0;
    for (int i = 1;i <= num / 2;++i)
        if (num % i == 0) tmp += i;
    if (num > tmp) cout << "Deficient\n";
    else if (num < tmp) cout << "Abundant\n";
    else cout << "Perfect\n";
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, T; cin >> T;
    while (T--) {
        cin >> N;
        solve(N);
    }
}