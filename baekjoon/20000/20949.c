#include <stdio.h>
#include <stdlib.h>

typedef struct elem {
    int w, h, i;
} elem;

int cmp(const void* lptr, const void* rptr) {
    const elem* l = (const elem*)lptr;
    const elem* r = (const elem*)rptr;
    const int lval = l->w * l->w + l->h * l->h;
    const int rval = r->w * r->w + r->h * r->h;
    if (lval == rval) {
        return l->i < r->i ? -1 : 1;
    }
    return lval > rval ? -1 : 1;
}

int main() {
    int n;
    scanf("%d", &n);
    elem* a = (elem*)malloc(sizeof(elem) * n);
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &a[i].w, &a[i].h);
        a[i].i = i + 1;
    }
    qsort(a, n, sizeof(elem), cmp);
    for (int i = 0; i < n; ++i) {
        printf("%d\n", a[i].i);
    }
}
