#include <cstdio>

int main() {
	int Q; scanf("%d", &Q);
	long long res_sum = 0;
	int res_xor = 0;

	while (Q--) {
		int q; scanf("%d", &q);
		if (q <= 2) {
			int x; scanf("%d", &x);
			res_sum += (q == 1 ? x : -x);
			res_xor ^= x;
		}
		else printf("%lld\n", q == 3 ? res_sum : res_xor);
	}
	return 0;
}