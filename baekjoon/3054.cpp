#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

void Peter(int n, char** arr, char c)
{
    int loc = 4 * n + 2, gap;
    arr[2][loc] = c;
    for (int i = 0; i < 5; i++) {
        gap = 2 - abs(2 - i);
        arr[i][loc + gap] = '#';
        arr[i][loc - gap] = '#';
    }
}
void Wendi(int n, char** arr, char c)
{
    int loc = 4 * n + 2, gap;
    arr[2][loc] = c;
    for (int i = 0; i < 5; i++) {
        gap = 2 - abs(2 - i);
        arr[i][loc + gap] = '*';
        arr[i][loc - gap] = '*';
    }
}

int main()
{
    string s; cin >> s;
    char** arr = new char* [5];
    int len = 4 * s.size() + 1;
    loop(i, 5) {
        arr[i] = new char[len];
        fill_n(arr[i], len, '.');
    }

    loop(i, s.size())
        if ((i + 1) % 3 != 0)
            Peter(i, arr, s[i]);
    loop(i, s.size())
        if ((i + 1) % 3 == 0)
            Wendi(i, arr, s[i]);

    loop(i, 5) {
        loop(j, len)cout << arr[i][j];
        cout << '\n';
    }
    return 0;
}