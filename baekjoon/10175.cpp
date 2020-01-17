#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string Name[4] = { "Bobcat","Coyote","Mountain Lion","Wolf" };
    int T; cin >> T;
    while (T--) {
        string Loc, S;
        cin >> Loc >> S;
        int arr[4] = {}, Len = S.size();
        loop(i, Len)
            if (S[i] == 'B') arr[0] += 2;
            else if (S[i] == 'C') arr[1] += 1;
            else if (S[i] == 'M') arr[2] += 4;
            else arr[3] += 3;
        int Max = 0, Max_spe;
        loop(i, 4)
            if (arr[i] > Max) {
                Max = arr[i];
                Max_spe = i;
            }
        cout << Loc << ": ";
        loop(i, 4)
            if (arr[i] == Max && i != Max_spe) {
                cout << "There is no dominant species\n";
                goto END;
            }
        cout << "The " << Name[Max_spe] << " is the dominant species\n";
    END:;
    }
    return 0;
}