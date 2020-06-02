#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 1000000;

int N;
int fenwick[max_N + 1];

void update(int i) {
    for (; i <= N; i += i & -i)
        ++fenwick[i];
}
int read(int i) {
    int ret = i;
    for (; i; i -= i & -i)
        ret -= fenwick[i];
    return ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    long long ans = 0;
    cin >> N;
    loop(i, N) {
        int x; cin >> x;
        ans += read(x - 1);
        update(x);
    }
    cout << ans;
    return 0;
}