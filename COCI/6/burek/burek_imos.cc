#define _GLIBCXX_DEBUG

#include <vector>
#include <cstdio>

using namespace std;

const int INF = 1000000000;
const int MAX = 1000000;

int main() {
    int N;
    scanf("%d", &N);
    vector<int> xbuf(MAX+1), ybuf(MAX+1, 0);
    for(int i = 0; i < N; ++i) {
        int l = INF, r = 0, b = INF, t = 0;
        for(int j = 0; j < 3; ++j) {
            int x, y;
            scanf("%d %d", &x, &y);
            l = min(l, x); r = max(r, x);
            b = min(b, y); t = max(t, y);
        }
        xbuf[l+1]++;
        xbuf[r]--;
        ybuf[b+1]++;
        ybuf[t]--;
    }
    int xacc = 0, yacc = 0;
    for(int i = 0; i <= MAX; ++i) {
        xacc += xbuf[i];
        xbuf[i] = xacc;
        yacc += ybuf[i];
        ybuf[i] = yacc;
    }

    int M;
    scanf("%d", &M);
    while(M--) {
        char axis;
        int pos;
        scanf(" %c = %d", &axis, &pos);
        int ans = 0;
        if(axis == 'x') {
            ans = xbuf[pos];
        } else {
            ans = ybuf[pos];
        }
        printf("%d\n", ans);
    }
    return 0;
}
