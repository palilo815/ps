#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
const int max_len = 500;

bool M[max_len][max_len];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    while (N--) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        for (int i = y1; i < y2; ++i)
            for (int j = x1; j < x2; ++j)
                M[i][j] = true;
    }

    int area = 0;
    loop(i, max_len) loop(j, max_len)
        if (M[i][j]) ++area;
    cout << area;
    return 0;
}