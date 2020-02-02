#include <iostream>
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, MIN = 1001, MAX = -1;
    cin >> n;
    while (n--) {
        int score; cin >> score;
        if (score > MAX) MAX = score;
        if (score < MIN) MIN = score;
    }
    cout << MAX - MIN;
    return 0;
}