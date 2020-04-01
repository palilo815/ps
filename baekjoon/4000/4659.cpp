#include <cstdio>
#include <cstring>

char pw[21];
int accept() {
    int moum = 0;
    int len = strlen(pw), cnt = 0;
    for (int i = 0; i < len; ++i) switch (pw[i]) {
    case 'a':
    case 'i':
    case 'u':
        if (pw[i + 1] == pw[i]) return 0;
    case 'e':
    case 'o':
        moum = 1;
        if (cnt > 0) {
            if (++cnt >= 3) return 0;
        }
        else cnt = 1;
        break;
    default:
        if (pw[i + 1] == pw[i]) return 0;
        if (cnt < 0) {
            if (--cnt <= -3) return 0;
        }
        else cnt = -1;
    }
    return moum;
}
int main() {
    while (1) {
        scanf("%s", pw);
        if (!strcmp(pw, "end")) break;
        printf("<%s> is %sacceptable.\n", pw, (accept() ? "" : "not "));
    }
    return 0;
}