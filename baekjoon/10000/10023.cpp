#include <cstdio>
#define loop(i,n) for(int i=0;i<n;++i)

const int max_N = 100;
const int max_B = 20;
const int max_V = 100001;
const int INF = 0x3f3f3f3f;

int breed[max_B];
int vol[max_N];

int DP[max_V];

int main() {
	int N, B; scanf("%d %d", &N, &B);
	loop(i, B) scanf("%d", &breed[i]);
	loop(i, N) scanf("%d", &vol[i]);

	loop(i, max_V) DP[i] = INF;
	DP[0] = 0;

	loop(b, B) loop(v, max_V - breed[b])
		if (DP[v + breed[b]] > DP[v] + 1)
			DP[v + breed[b]] = DP[v] + 1;

	int prv = 0, ans = 0;
	loop(i, N) {
		vol[i] -= prv;
		if (DP[vol[i]] == INF) {
			printf("-1");
			return 0;
		}
		ans += DP[vol[i]];
		prv += vol[i];
		if (prv) --prv;
	}
	printf("%d", ans);
	return 0;
}