#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 50;

bool frnd[max_N][max_N];

int main() {
    int N; cin >> N;
    char x;
    loop(i, N) loop(j, N) {
        cin >> x;
        if (x == 'Y') frnd[i][j] = true;
    }
    
    int ans = 0;
    loop(i, N) {
        int cnt = 0;
        loop(j, N) if (i != j) {
            if (frnd[i][j]) ++cnt;
            else loop(k, N) if (frnd[i][k] && frnd[k][j]) {
                ++cnt; break;
            }
        }
        if (cnt > ans) ans = cnt;
    }
    cout << ans;
    return 0;
}