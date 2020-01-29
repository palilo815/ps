//#include <stdio.h>
//#define found he
//const char* prob = "70i02@67H07P6dQb3@7e"
//"Rb3X7eOfaY64TceG5dyd4r5dr1bL10^21H";
//void pr(const char*, int*);
//void hehe() { int k = 0; pr(prob, &k); }
//float sr(float y) {
//    int i = 0x5f3759df - ((*(int*)&y) >> 1);
//    float x2 = y * 0.5F; y = *(float*)&i;
//    y = y * (1.5F - (x2 * y * y)); return y * (1.5F - (x2 * y * y));
//}
//char p[1 << 16], * a = p;
//
//#define v(b) *a++=(b)
//int tt = 0, vv = 2, ww = 5;
//int rd() {
//    tt = (tt * 2 + tt * tt * 7 + vv * 13 + vv * vv * 17 + ww * 5 + ww * ww * 6) % 84;
//    vv = (tt * 3 + tt * tt * 4 + vv * 2 + vv * vv * 11 + ww * 2 + ww * ww * 10) % 1241;
//    ww = (tt * 4 + tt * tt * 3 + vv * 7 + vv * vv * 13 + ww + ww * ww * 12) % 5883;
//    return tt;
//}
//const char* func = "2a#05H6bu07G21h42U26n3bU37>e9H41!eb}35i34p3a(3a"
//"*"                                                     "e6K44ve5N56<ca%9e]c7Xa1hc4>64]c5wb6Mb3gbbkb9x67]04M39Gf7<44Wd"
//"cx"                                                   "94mde^4ai26#4c!23H3f<edj39k32jf7i44rdc a1<8e&9c%";
//const char* u = "!@#$%^&*()1234567890QWERTYUIOPqwertyuiopASD"
//"FG"                                                 "HJKLasdfghjklZXCVBNMzxcvbnm,./<>?{}[]+=";
//const char* def = "2ai05i1eS46s1fy47#22v4c&1"
//"9u"                                               "07o5f^10u65Q09R5b%c5%a3!c2I6dzbdZ";
//void pr(const char* t, int* k) {
//    unsigned int w = 0, c;
//    while (*t) {
//        sscanf(t, "%x", &c); c = (c + w) % 256;
//        w = (c - w + 256) % 0x100; v(c); t += 3; (*k)++;
//    }
//    (*k)--;
//}
//const char* pr1 = "2aK05I5eQ0aZ57o1bs05U25]4bI27Z48g1a)06j37i"
//"e9w39Xfev"                             "32V37Hf9g39m07Z2f[08p40qf0v47*09W2dG37s1aI48hebX55ge2h83R9fx90&9ag";
//
//const char* pr2 = "2au05!1dp35v2d>06P52He5k80xcfy97wca[8fna7g8dSc7}9cLc9(7esb7Uad{cct98X9cOd6*5fH05j6d}c4(9eOaek"
//"83Sadkb1I81gb0h98q8a<b1$7e@acn";
//void half() {
//    int i, j, k, l;
//    for (i = 60; i >= 0; i--) {
//        j = 1. / sr(3600 - i * i);
//        l = 1. / sr(900 - i * i);
//        for (k = 0; k < 60 - j; k++)v(' '); v('/'); v('*');
//        for (k++; k < 60 + j; k++) {
//            if (0 <= i && i < 30) {
//                if (i == 10 && k == 90)pr(def, &k);
//                else if (i == 8 && k == 70)pr(pr1, &k);
//                else if (i == 6 && k == 70)pr(pr2, &k);
//                else if (i == 2 && k == 63)pr(func, &k);
//                else v((90 - l <= k && k <= 90 + l) ? u[rd()] : ' ');
//            }
//            else v(' ');
//        }v('*'); v('/'); v('\n');
//    }
//}
//
//int main() {
//#ifdef found
//    hehe();
//#else
//    half();
//#endif
//    return puts(p);
//}

//  **  print 111x ^ 2 + 11x + 1  **
#include <stdio.h>

int main()
{
    int x;
    scanf("%d", &x);
    printf("%d", 111 * x * x + 11 * x + 1);
    return 0;
}