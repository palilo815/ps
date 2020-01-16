#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int k;
char arr[9];
bool Used[10];
string Ans_Big, Ans_Sma;
void Biiig(int prev, int ind, string s)
{
    if (Ans_Big.length()) return;
    if (ind == k) {
        Ans_Big = s;
        return;
    }
    Used[prev] = true;
    char c = arr[ind];
    if (c == '>') {
        for (int i = prev - 1; i >= 0; --i)
            if (!Used[i])
                Biiig(i, ind + 1, s + to_string(i));
    }
    else {
        for (int i = 9; i > prev; --i)
            if (!Used[i])
                Biiig(i, ind + 1, s + to_string(i));
    }
    Used[prev] = false;
}
void Smmma(int prev, int ind, string s)
{
    if (Ans_Sma.length()) return;
    if (ind == k) {
        Ans_Sma = s;
        return;
    }
    Used[prev] = true;
    char c = arr[ind];
    if (c == '>') {
        for (int i = 0; i < prev; ++i)
            if (!Used[i])
                Smmma(i, ind + 1, s + to_string(i));
    }
    else {
        for (int i = prev + 1; i < 10; ++i)
            if (!Used[i])
                Smmma(i, ind + 1, s + to_string(i));
    }
    Used[prev] = false;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> k;
    loop(i, k) cin >> arr[i];

    for (int i = 9; i >= 0; --i)
        if (Ans_Big.length() == 0) {
            Biiig(i, 0, to_string(i));
        }
    for (int i = 0; i < 10; ++i)
        if (Ans_Sma.length() == 0) {
            Smmma(i, 0, to_string(i));
        }
    cout << Ans_Big << '\n' << Ans_Sma;
    return 0;
}