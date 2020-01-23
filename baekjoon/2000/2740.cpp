#include<iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int A[100][100], B[100][100];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M, K;
    cin >> N >> M;
    loop(i, N) loop(j, M) cin >> A[i][j];
    cin >> M >> K;
    loop(i, M) loop(j, K) cin >> B[i][j];
    loop(n, N) {
        loop(k, K) {
            int x = 0;
            loop(m, M) x += A[n][m] * B[m][k];
            cout << x << ' ';
        }
        cout << '\n';
    }
    return 0;
}