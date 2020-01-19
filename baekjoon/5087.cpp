#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int C = 0, T = 0;
    string Card;
    while (cin >> Card) {
        if (Card == "#") break;
        if (Card == "*") {
            if (C < T) cout << "Tania\n";
            else if (C > T) cout << "Cheryl\n";
            else cout << "Draw\n";
            C = T = 0;
        }
        else {
            if (Card == "A") Card = "1";
            int Num = stoi(Card);
            if (Num % 2) ++C;
            else ++T;
        }
    }
    return 0;
}