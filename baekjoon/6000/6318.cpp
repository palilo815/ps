#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int BLOCK[50];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, S = 1;
    while (cin >> n) {
        if (n == 0) break;
        int sum = 0;
        loop(i, n) {
            cin >> BLOCK[i];
            sum += BLOCK[i];
        }
        int ave = sum / n, H = 0, L = 0;
        loop(i, n) {
            if (BLOCK[i] > ave) H += BLOCK[i] - ave;
            else if (BLOCK[i] < ave) L += ave - BLOCK[i];
        }
        if (S > 1) cout << '\n';
        cout << "Set #" << S++ << '\n';
        cout << "The minimum number of moves is " << max(H, L) << ".\n";
    }
    return 0;
}