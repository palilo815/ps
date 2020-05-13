#include <cstdio>
#include <cstring>

typedef struct {
	char arr[1000001];
	int sz;
	void init() { sz = 0; }
	void push(char x) {
		arr[sz++] = x;
		if (sz >= 4 && !strncmp(arr + sz - 4, "PPAP", 4))
			sz -= 3;
	}
	int PPAP() {
		return sz == 1 && arr[0] == 'P';
	}
} stack;

char s[1000001];

int main() {
	stack stk;
	stk.init();

	scanf("%s", s);
	for (int i = 0; s[i]; ++i)
		stk.push(s[i]);
	printf("%s", (stk.PPAP() ? "PPAP" : "NP"));
	return 0;
}