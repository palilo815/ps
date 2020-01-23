#include <iostream>
#include <algorithm>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef struct student {
    string name;
    int Kor;
    int Eng;
    int Math;
}Stu;

bool MySort(Stu a, Stu b)
{
    if (a.Kor == b.Kor) {
        if (a.Eng == b.Eng) {
            if (a.Math == b.Math)
                return a.name < b.name;
            else return a.Math > b.Math;
        }
        else return a.Eng < b.Eng;
    }
    else return a.Kor > b.Kor;
}
int main()
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int n; cin >> n;
    Stu* arr = new Stu[n];
    loop(i, n)
        cin >> arr[i].name >> arr[i].Kor >> arr[i].Eng >> arr[i].Math;
    sort(arr, arr + n, MySort);
    loop(i, n)
        cout << arr[i].name << '\n';
    return 0;
}