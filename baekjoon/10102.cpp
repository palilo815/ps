#include <iostream>
using namespace std;

int main()
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int V, sum = 0;
    cin >> V;
    while (V--) {
        char c; cin >> c;
        if (c == 'A') ++sum;
        else --sum;
    }
    if (sum > 0) cout << 'A';
    else if (sum < 0) cout << 'B';
    else cout << "Tie";
    return 0;
}