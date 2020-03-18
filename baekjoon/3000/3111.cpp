#include <stdio.h>
#include <string.h>

const int max_T = 300000;
const int max_key = 25;

char txt[max_T + 1];
char key[max_key + 1];

typedef struct {
    int top, key_len;
    char* arr, * key;
    void init(int sz, char* k, int k_len) {
        top = 0;
        arr = new char[sz + 1];
        key_len = k_len;
        key = new char[k_len + 1];
        strcpy(key, k);
    }
    bool push(char x) {
        arr[top++] = x;
        if (key_len > top) return false;
        bool erase = true;
        for (int i = 0; i < key_len; ++i)
            if (arr[top - 1 - i] != key[i]) {
                erase = false;
                break;
            }
        if (erase) top -= key_len;
        return erase;
    }
    char pop() {
        return arr[--top];
    }
    bool empty() { return (top == 0); }
} stack;

int main() {
    scanf("%s", key);
    scanf("%s", txt);

    int t_len = strlen(txt);
    int k_len = strlen(key);

    stack L, R;
    R.init(t_len, key, k_len);
    int i = 0, j = k_len - 1;
    while (i < j) {
        char tmp = key[i];
        key[i] = key[j];
        key[j] = tmp;
        ++i, --j;
    }
    L.init(t_len, key, k_len);
    int l = 0, r = t_len - 1;
    bool flag = false;

    while (l <= r) {
        if (flag) flag ^= R.push(txt[r--]);
        else flag ^= L.push(txt[l++]);
    }

    while (!L.empty())
        R.push(L.pop());
    while (!R.empty())
        putchar(R.pop());
    return 0;
}