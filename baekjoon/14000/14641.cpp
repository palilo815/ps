#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

bool trans[26][26];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int M, N; cin >> M >> N;
    while (M--) {
        char u, v; cin >> u >> v;
        trans[u - 'a'][v - 'a'] = true;
    }

    loop(i, 26) trans[i][i] = true;
    loop(k, 26) loop(i, 26) loop(j, 26)
        trans[i][j] = trans[i][j] | (trans[i][k] & trans[k][j]);

    string src, dst;
    while (N--) {
        cin >> src >> dst;
        if (src.size() != dst.size()) {
            cout << "no\n";
            continue;
        }
        bool valid = true;
        int L = src.size();
        loop(i, L) {
            char u = src[i], v = dst[i];
            if (!trans[u - 'a'][v - 'a']) {
                valid = false;
                break;
            }
        }
        cout << (valid ? "yes" : "no") << '\n';
    }
    return 0;
}