//Name: Barn Expansion
//Level: 3
//Category: 座標圧縮,イベントドリブン,Event Driven
//Note:

/**
 * 水平方向と垂直方向は独立に考えられる。
 *
 * 同じ軸上に乗っている点をなめながら、開始点でネストレベルを加算、終了点で減算する。
 * ネストレベルが2以上になったら、この連結成分に関連する矩形はすべて拡張不可能であるので、
 * ネストレベルが0になるまで、すべての頂点についてその属する矩形のフラグを下ろす。
 * （こうすることで、(0, 3), (1, 2)のような完全に内包する形を処理できる）
 *
 * オーダーはO(N log N)。
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

enum TagType {
    TAG_OPEN,
    TAG_CLOSE
};

struct Tag {
    int ord, pos, id;
    TagType type;

    Tag() {}
    Tag(int o, int p, int id, TagType t) : ord(o), pos(p), id(id), type(t) {}

    bool operator <(const Tag &other) const {
        if(ord != other.ord) return ord < other.ord;
        if(pos != other.pos) return pos < other.pos;
        return type < other.type;
    }
};

Tag verticals[200000], horizontals[200000];
int N;
bool ok[25000];

void traverse(const Tag *start, const Tag *end) {
    int level = 0;
    const Tag *t = start;
    int prev_ord = -1;
    bool invalid = false;
    while(t != end) {
        if(t->ord != prev_ord) {
            level = 0;
            invalid = false;
            prev_ord = t->ord;
        }
        const int pos = t->pos;
        while(t != end && t->pos == pos && t->ord == prev_ord) {
            if(invalid) ok[t->id] = false;
            if(t->type == TAG_OPEN) {
                ++level;
                if(level >= 2) invalid = true;
            }
            if(t->type == TAG_CLOSE) {
                --level;
                if(level == 0) invalid = false;
            }
            //printf("%d %d %d %d\n", t->ord, t->pos, level, invalid);
            ++t;
        }
    }
}

bool solve() {
    if(scanf("%d", &N) == EOF) return false;
    for(int i = 0; i < N; ++i) {
        int a, b, c, d;
        scanf("%d %d %d %d", &a, &b, &c, &d);
        verticals[i*4] = Tag(a, b, i, TAG_OPEN);
        verticals[i*4+1] = Tag(a, d, i, TAG_CLOSE);
        verticals[i*4+2] = Tag(c, b, i, TAG_OPEN);
        verticals[i*4+3] = Tag(c, d, i, TAG_CLOSE);
        horizontals[i*4] = Tag(b, a, i, TAG_OPEN);
        horizontals[i*4+1] = Tag(b, c, i, TAG_CLOSE);
        horizontals[i*4+2] = Tag(d, a, i, TAG_OPEN);
        horizontals[i*4+3] = Tag(d, c, i, TAG_CLOSE);
    }
    sort(verticals, verticals+N*4);
    sort(horizontals, horizontals+N*4);
    fill_n(ok, N, true);
    traverse(verticals, verticals+N*4);
    traverse(horizontals, horizontals+N*4);
    int ans = 0;
    for(int i = 0; i < N; ++i) {
        if(ok[i]) ++ans;
    }
    printf("%d\n", ans);
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
