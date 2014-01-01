//Name: Best Cow Line, Gold
//Level: 3
//Category: 貪欲,Greedy
//Note:

/**
 * 基本的には小さいほうの文字を優先的に出力する。
 * 候補が2つとも同じ文字の時は、それ以降に出現する文字列を辞書順で比較し、小さいほうを先に出力する。
 *
 * オーダーはO(N^2)。
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#define FOREACH(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

char cows[30000];
char res[30001];
bool solve() {
    int N;
    if(scanf("%d", &N) == EOF) return false;
    if(!N) return false;

    TIMES(i, N) {
        scanf(" %c", cows+i);
    }
    int l = 0, r = N-1;
    int pos = 0;
    while(pos < N) {
        if(cows[l] < cows[r]) {
            res[pos++] = cows[l++];
        } else if(cows[l] > cows[r]) {
            res[pos++] = cows[r--];
        } else {
            int lp = l, rp = r;
            int flag = 0;
            while(lp <= rp) {
                if(cows[lp] < cows[rp]) {
                    flag = -1;
                    break;
                } else if(cows[lp] > cows[rp]) {
                    flag = 1;
                    break;
                }
                ++lp; --rp;
            }
            if(flag <= 0) {
                res[pos++] = cows[l++];
            } else {
                res[pos++] = cows[r--];
            }
        }
    }
    TIMES(i, N) {
        printf("%c", res[i]);
        if(i % 80 == 79 || i == N-1) puts("");
    }
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
