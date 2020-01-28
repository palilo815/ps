#include <iostream>
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T, hp, mp, atk, arm, hp_pm, mp_pm, atk_pm, arm_pm;
    cin >> T;
    while (T--) {
        cin >> hp >> mp >> atk >> arm >> hp_pm >> mp_pm >> atk_pm >> arm_pm;
        int stat = 0;
        stat += (hp + hp_pm < 1) ? 1 : hp + hp_pm;
        stat += (mp + mp_pm < 1) ? 5 : 5 * (mp + mp_pm);
        stat += (atk + atk_pm < 0) ? 0 : 2 * (atk + atk_pm);
        stat += 2 * (arm + arm_pm);
        cout << stat << '\n';
    }
    return 0;
}