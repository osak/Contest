//Name: Packets
//Level: 2
//Category: Math,数学,場合分け
//Note:

/*
 * Put large productes to smaller products in this order.
 * - A 6*6 needs exactly 1 parcel per product.
 * - A 5*5 can be put into 1 parcel, with filling the gap with 1*1s (up to 11.)
 * - A 4*4 can be put into 1 parcel, with filling the gap with 2*2s (up to 5.)
 *   If there is more gap, it can be filled with 1*1s.
 * - At most four 3*3s can be put into 1 parcel.
 *   The gap can be filled with five or three or one 2*2s, depending on how many 3*3s are put in.
 * - At most nine 2*2s can be put int 1 parcel, with filling the gap with 1*1s.
 *
 * This algorithm runs in O(1).
 */
#include <cstdio>
#include <algorithm>

using namespace std;

bool solve() {
    int a, b, c, d, e, f;
    scanf("%d %d %d %d %d %d", &a, &b, &c, &d, &e, &f);
    if(!a && !b && !c && !d && !e && !f) return false;

    int ans = 0;
    ans += f; // 6*6
    ans += e; // 5*5
    a = max(0, a - e*11);
    ans += d; // 4*4
    if(b >= d*5) {
        b -= d*5;
    } else {
        d -= b / 5;
        if(b % 5) {
            a = max(0, a - (5 - b%5) * 4);
            --d;
        }
        b = 0;
        a = max(0, a - d*20);
    }
    ans += (c+3) / 4; // 3*3
    c %= 4;
    int v = 36 - 9*c;
    if(c == 1) {
        v -= min(5, b)*4;
        b = max(0, b-5);
    } else if(c == 2) {
        v -= min(3, b)*4;
        b = max(0, b-3);
    } else if(c == 3) {
        v -= min(1, b)*4;
        b = max(0, b-1);
    }
    if(c) a = max(0, a - v);
    ans += (b+8)/9; // 2*2
    if(b % 9) {
        a = max(0, a - (9 - b%9) * 4);
    }
    ans += (a+35) / 36; // 1*1

    printf("%d\n", ans);
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
