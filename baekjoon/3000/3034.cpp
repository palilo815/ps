#include <iostream>
using namespace std;

int main()
{
    int N, W, H, max_len;
    cin >> N >> W >> H;
    for (int i = 0; i * i <= W * W + H * H; ++i)
        max_len = i;
    while (N--) {
        int len; cin >> len;
        if (len <= max_len)
            cout << "DA";
        else
            cout << "NE";
        cout << endl;
    }
    return 0;
}