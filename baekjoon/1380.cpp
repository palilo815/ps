#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

bool Apsu[100];
int main()
{
    cin.tie(NULL); cout.tie(NULL);
    std::ios::sync_with_stdio(false);

    int n, T = 0;
    string Name[100];
    while (cin >> n) {
        if (n == 0) break;
        memset(Apsu, 0, sizeof(Apsu));
        cin.ignore();
        loop(i, n) getline(cin, Name[i]);

        loop(i, 2 * n - 1) {
            int num; char c;
            cin >> num >> c;
            Apsu[num - 1] = !Apsu[num - 1];
        }

        cout << ++T << ' ';
        loop(i, n) if (Apsu[i]) {
            cout << Name[i] << '\n';
            break;
        }
    }
    return 0;
}