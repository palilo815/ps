#include <iostream>
using namespace std;
const int max_N = 100000;

int psum[max_N + 1];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n; cin >> n;
    int x;
    for (int i = 1;i <= n;++i) {
        cin >> x;
        psum[i] = psum[i - 1] + x;
    }
    cin >> n;
    int a, b;
    while (n--) {
        cin >> a >> b;
        cout << psum[b + 1] - psum[a] << '\n';
    }
    return 0;
}