#include <stdio.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define swap(a,b) do{int tmp=a;a=b;b=tmp;}while(0)

int main()
{
    char c;
    int cup[3] = { 1, };
    while (scanf("%c", &c)) {
        if (c == '\n') break;
        if (c == 'A') swap(cup[0], cup[1]);
        else if (c == 'B') swap(cup[1], cup[2]);
        else if (c == 'C') swap(cup[0], cup[2]);
    }
    loop(i, 3)
        if (cup[i]) printf("%d", i + 1);
    return 0;
}