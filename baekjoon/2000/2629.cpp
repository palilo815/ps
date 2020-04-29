#include<bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_W = 15000;

bool DP[max_W + 1];
bool tmp[max_W + 1];

int main() {
	cin.tie(0), cout.tie(0);
	ios::sync_with_stdio(0);

	int N; cin >> N;
	DP[0] = true;

	while (N--) {
		int w; cin >> w;
		loop(i, max_W + 1) if (DP[i]) {
			if (i + w <= max_W) tmp[i + w] = true;
			tmp[abs(i - w)] = true;
		}
		DP[w] = true;

		loop(i, max_W + 1) {
			DP[i] |= tmp[i];
			tmp[i] = false;
		}
	}

	int Q; cin >> Q;
	while (Q--) {
		int w; cin >> w;
		cout << (DP[w] ? 'Y' : 'N') << ' ';
	}
	return 0;
}