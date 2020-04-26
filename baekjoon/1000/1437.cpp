#include <cstdio>

const int mod = 10007;

int main() {
	int N; scanf("%d", &N);
	int three = N / 3; N %= 3;
	int two = N == 2;
	int one = N == 1;

	int ans = (one || two || three);
	if (one && three) --one, --three, two += 2;

	for (int i = 0; i < three; ++i)
		ans = ans * 3 % mod;
	for (int i = 0; i < two; ++i)
		ans = ans * 2 % mod;
	printf("%d", ans);
	return 0;
}