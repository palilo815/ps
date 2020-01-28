#include<iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 100;
char mirror[max_N][max_N];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    loop(i, N) loop(j, N) cin >> mirror[i][j];

    int mood; cin >> mood;
    if (mood == 1)
        loop(i, N) {
        loop(j, N) cout << mirror[i][j];
        cout << '\n';
    }
    else if (mood == 2)
        loop(i, N) {
        for (int j = N - 1;j >= 0;--j) cout << mirror[i][j];
        cout << '\n';
    }
    else
        for (int i = N - 1;i >= 0;--i) {
            loop(j, N) cout << mirror[i][j];
            cout << '\n';
        }
    return 0;
}