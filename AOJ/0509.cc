//Name: Sheets
//Level: 3
//Category: 座標圧縮
//Note:

/*
 * 座標の範囲が狭いので，一度に一つの軸だけを圧縮して考えれば事足りる．
 * 面積は1軸，周長は2軸で測定する必要がある．
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

struct Tag {
    int a;
    int b1, b2;
    bool start;

    Tag() : a(0), b1(0), b2(0), start(false) {}
    Tag(int aa, int bb1, int bb2, bool s) : a(aa), b1(bb1), b2(bb2), start(s) {}
};

bool cmp(const Tag &t1, const Tag &t2) {
    if(t1.a != t2.a) return t1.a < t2.a;
    return !t1.start;
}

int main() {
    while(true) {
        int N, R;
        cin >> N >> R;
        if(!N && !R) break;

        vector<Tag> xtag, ytag;
        for(int i = 0; i < N; ++i) {
            int x1, y1, x2, y2;
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            xtag.push_back(Tag(x1, y1, y2, true));
            xtag.push_back(Tag(x2, y1, y2, false));
            ytag.push_back(Tag(y1, x1, x2, true));
            ytag.push_back(Tag(y2, x1, x2, false));
        }
        sort(xtag.begin(), xtag.end(), cmp);
        sort(ytag.begin(), ytag.end(), cmp);

        int max_y = ytag[ytag.size()-1].a;
        int area = 0;
        int len = 0;
        for(int y = 0; y < max_y; ++y) {
            int depth = 0;
            int startx = 0;
            int prevx = -1;
            for(int i = 0; i < xtag.size(); ++i) {
                if(xtag[i].b1 <= y && y < xtag[i].b2) {
                    if(xtag[i].start) {
                        if(depth == 0) {
                            if(xtag[i].a != prevx) ++len;
                            else --len;
                            startx = xtag[i].a;
                        }
                        ++depth;
                    }
                    else {
                        if(--depth == 0) {
                            area += xtag[i].a-startx;
                            prevx = xtag[i].a;
                            ++len;
                        }
                    }
                }
            }
        }

        cout << area << endl;
        if(R == 1) continue;

        int max_x = xtag[xtag.size()-1].a;
        for(int x = 0; x < max_x; ++x) {
            int depth = 0;
            int prevy = -1;
            for(int i = 0; i < ytag.size(); ++i) {
                if(ytag[i].b1 <= x && x < ytag[i].b2) {
                    if(ytag[i].start) {
                        if(depth == 0) {
                            if(prevy != ytag[i].a) ++len;
                            else --len;
                        }
                        ++depth;
                    }
                    else {
                        if(--depth == 0) {
                            ++len;
                            prevy = ytag[i].a;
                        }
                    }
                }
            }
        }
        cout << len << endl;
    }
    return 0;
}
