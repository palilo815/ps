#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
const int max_N = 1000000;

int a[max_N], b[max_N];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    int A, B;
    loop(i, N) {
        cin >> a[i];
        if (a[i] == 1) A = i;
    }
    loop(i, N) {
        cin >> b[i];
        if (b[i] == 1) B = i;
    }

    int dir = 0;
    if (a[(A + 1) % N] == b[(B + 1) % N]) dir = 1;
    else if (a[(A + 1) % N] == b[(B + N - 1) % N]) dir = -1;

    bool good;
    if (dir == 0) good = false;
    else {
        int i = A, j = B;
        good = true;
        do {
            if (a[i] != b[j]) {
                good = false;
                break;
            }
            i = (i + 1) % N;
            j = (j + dir + N) % N;
        } while (i != A);
    }
    if (good) cout << "good";
    else cout << "bad";
    cout << " puzzle";
    return 0;
}