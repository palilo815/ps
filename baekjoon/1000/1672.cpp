#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int DNA[1000000];
int decode[4][4] = { {0,2,0,1},{2,1,3,0},{0,3,2,1},{1,0,1,3} };
int conv(char c) {
    switch (c) {
    case 'A':return 0;
    case 'G':return 1;
    case 'C':return 2;
    case 'T':return 3;
    }
    return -1;
}
char rev(int n) {
    switch (n) {
    case 0:return 'A';
    case 1:return 'G';
    case 2:return 'C';
    case 3:return 'T';
    }
    return '\0'; // 의미 없음
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    loop(i, N) {
        char c; cin >> c;
        DNA[i] = conv(c);
    }
    while (--N)
        DNA[N - 1] = decode[DNA[N - 1]][DNA[N]];
    cout << rev(DNA[0]);
    return 0;
}