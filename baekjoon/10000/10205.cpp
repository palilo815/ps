#include <stdio.h>

int main()
{
    int T, head;
    char s[101];
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t) {
        scanf("%d", &head);
        scanf("%s", s);
        for (int i = 0; s[i] != '\0'; ++i)
            if (s[i] == 'c') ++head;
            else --head;
        printf("Data Set %d:\n%d\n\n", t, head);
    }
    return 0;
}