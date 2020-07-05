#include <bits/stdc++.h>
#define pb pop_back()
#define eb emplace_back
using namespace std;
using tup = tuple<int, string, string, string>;

string str, tmp;
vector<tup> vt;

bool contradiction;

void S() {
    if (contradiction) return;
    str.pb;
    stringstream ss(str);
    int neg = 0;

    string subj; ss >> subj;
    if (subj == "nobody")
        neg = 1, subj = "everybody";

    string verb; ss >> verb;
    if (verb == "don't" || verb == "doesn't") {
        neg = 1;
        ss >> verb;
    }
    else if (subj != "I" && subj != "you")
        verb.pb;

    string obj;
    while (ss >> tmp)
        obj += tmp + " ";
    if (obj.size()) obj.pb;

    if (subj == "everybody") {
        for (auto& [n, s, v, o] : vt)
            if (neg ^ n && verb == v && obj == o) {
                contradiction = true;
                return;
            }
    }
    else {
        for (auto& [n, s, v, o] : vt)
            if (neg ^ n && (s == "everybody" || subj == s) && verb == v && obj == o) {
                contradiction = true;
                return;
            }
    }
    vt.eb(neg, subj, verb, obj);
}
void Q() {
    cout << str << '\n';
    if (contradiction) {
        cout << "I am abroad.\n\n";
        return;
    }

    str.pb;
    stringstream ss(str);
    vector<string> ans;

    ss >> tmp;
    if (tmp == "what") {
        string subj; ss >> tmp >> subj;
        for (auto& [neg, s, v, o] : vt) {
            if (s == "everybody" || subj == s) {
                if (neg) tmp = (subj == "I" || subj == "you" ? "don't " : "doesn't ") + v;
                else tmp = v + (subj == "I" || subj == "you" ? "" : "s");
                if (o.size()) tmp += " " + o;
                ans.eb(tmp);
            }
        }
        if (ans.empty()) {cout << "I don't know.\n\n"; return;}

        if (subj == "I") subj = "you";
        else if (subj == "you") subj = "I";
        cout << subj << ' ';
        for (int i = 0; i < ans.size(); ++i) {
            if (i) cout << (i ^ ans.size() - 1 ? ", " : ", and ");
            cout << ans[i];
        }
    }
    else if (tmp == "who") {
        string verb, obj; ss >> verb;
        verb.pb;
        while (ss >> tmp) obj += tmp + " ";
        if (obj.size()) obj.pb;

        for (auto& [neg, s, v, o] : vt)
            if (verb == v && obj == o) {
                if (neg && s == "everybody") {ans = {"nobody"}; break;}
                else if (!neg) {
                    if (s == "everybody") {ans = {"everybody"}; break;}
                    if (s == "I") ans.eb("you");
                    else if (s == "you") ans.eb("I");
                    else ans.eb(s);
                }
            }
        if (ans.empty()) {cout << "I don't know.\n\n"; return;}
        if (ans.size() == 1 && ans[0] != "I" && ans[0] != "you")
            verb += 's';

        for (int i = 0; i < ans.size(); ++i) {
            if (i) cout << (i ^ ans.size() - 1 ? ", " : " and ");
            cout << ans[i];
        }
        cout << ' ' << verb;
        if (obj.size()) cout << ' ' << obj;
    }
    else {
        string subj, verb, obj; ss >> subj >> verb;
        while (ss >> tmp) obj += tmp + " ";
        if (obj.size()) obj.pb;

        int no = -1;
        for (auto& [neg, s, v, o] : vt)
            if ((s == "everybody" || subj == s) && verb == v && obj == o) {
                no = neg;
                break;
            }
        if (no == -1) {cout << "maybe.\n\n"; return;}

        if (subj == "I") subj = "you";
        else if (subj == "you") subj = "I";

        if (no) verb = ((subj == "I" || subj == "you") ? "don't " : "doesn't ") + verb;
        else if (subj != "I" && subj != "you") verb += 's';

        cout << (no ? "no, " : "yes, ") << subj << ' ' << verb;
        if (obj.size()) cout << ' ' << obj;
    }
    cout << ".\n\n";
}
int main() {
    int T; cin >> T; cin.ignore();
    for (int t = 1, flag = 1; t <= T; ++t) {
        vt.clear();
        flag = 1, contradiction = false;

        cout << "Dialogue #" << t << ":\n";
        while (flag) {
            getline(cin, str);
            switch (str.back()) {
            case '.': S(); break;
            case '?': Q(); break;
            default:
                cout << str << '\n' << '\n';
                flag = 0;
            }
        }
    }
    return 0;
}