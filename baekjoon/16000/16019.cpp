#include<iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    int dist[5];
    dist[0] = 0;
    loop(i, 4) {
        int x; cin >> x;
        dist[i + 1] = dist[i] + x;
    }
    loop(i, 5) {
        loop(j, 5) {
            if (i < j) cout << dist[j] - dist[i];
            else cout << dist[i] - dist[j];
            cout << ' ';
        }
        cout << '\n';
    }
    return 0;
}