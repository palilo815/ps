#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int quadtree[512][512];
void decode(string::iterator& it, int y, int x, int len)
{
    char head = *(it++);
    if (head != 'Q') {
        int colour = (head == 'B');
        loop(dy, len) loop(dx, len)
            quadtree[y + dy][x + dx] = colour;
    }
    else {
        int half = len / 2;
        decode(it, y, x, half);
        decode(it, y, x + half, half);
        decode(it, y + half, x, half);
        decode(it, y + half, x + half, half);
    }
}

int main()
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int n;
    string code;
    cin >> n >> code;

    auto it = code.begin();
    decode(it, 0, 0, n);

    cout << "#define quadtree_width " << n << '\n';
    cout << "#define quadtree_height " << n << '\n';
    cout << "static char quadtree_bits[] = {\n";
    cout << hex;
    loop(i, n) {
        for (int j = 0;j < n;j += 8) {
            int sum = 0;
            loop(k, 8) sum += quadtree[i][j + k] * pow(2, k);
            cout << "0x" << std::setfill('0') << std::setw(2) << sum << ',';
        }
        cout << '\n';
    }
    cout << "};";
    return 0;
}