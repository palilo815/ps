#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> p;

const int max_N = 100000;

int use[max_N];
p in[max_N];
p out[max_N];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    loop(i, N) {
        cin >> in[i].first;
        in[i].second = i;
        cin >> out[i].first;
        out[i].second = i;
    }

    sort(in, in + N);
    sort(out, out + N);
    
    priority_queue<int, vector<int>, greater<int>> pq;
    int com = 0, i = 0, j = 0;
    while (i < N) {
        if (in[i].first < out[j].first) {
            if (pq.empty()) use[in[i].second] = com++;
            else {
                use[in[i].second] = pq.top();
                pq.pop();
            }
            ++i;
        }
        else {
            pq.push(use[out[j].second]);
            ++j;
        }
    }
    
    vector<int> cnt(com);
    loop(i, N) ++cnt[use[i]];
    cout << com << '\n';
    for (int x : cnt) cout << x << ' ';
    return 0;
}