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
        stable_sort(ytag.begin(), ytag.end(), cmp);

        int max_y = ytag[ytag.size()-1].a;
        int area = 0;
        int len = 0;
        int prev_y = -1;
        int prev_area = 0;
        int prev_len = 0;
        for(int j = 0; j < ytag.size(); ++j) {
            if(prev_y == ytag[j].a) continue;
            area += prev_area * (ytag[j].a-prev_y);
            len += prev_len * (ytag[j].a-prev_y);
            prev_y = ytag[j].a;
            prev_area = 0;
            prev_len = 0;

            int depth = 0;
            int startx = 0;
            int prevx = -1;
            for(int i = 0; i < xtag.size(); ++i) {
                if(xtag[i].b1 <= prev_y && prev_y < xtag[i].b2) {
                    if(xtag[i].start) {
                        if(depth == 0) {
                            if(xtag[i].a != prevx) ++prev_len;
                            else --prev_len;
                            startx = xtag[i].a;
                        }
                        ++depth;
                    }
                    else {
                        if(--depth == 0) {
                            prev_area += xtag[i].a-startx;
                            prevx = xtag[i].a;
                            ++prev_len;
                        }
                    }
                }
            }
        }

        cout << area << endl;
        if(R == 1) continue;

        prev_len = 0;
        int prev_x = -1;
        for(int j = 0; j < xtag.size(); ++j) {
            if(prev_x == xtag[j].a) continue;
            len += prev_len * (xtag[j].a-prev_x);
            prev_x = xtag[j].a;
            prev_len = 0;

            int depth = 0;
            int prevy = -1;
            for(int i = 0; i < ytag.size(); ++i) {
                if(ytag[i].b1 <= prev_x && prev_x < ytag[i].b2) {
                    if(ytag[i].start) {
                        if(depth == 0) {
                            if(ytag[i].a != prevy) ++prev_len;
                            else --prev_len;
                        }
                        ++depth;
                    }
                    else {
                        if(--depth == 0) {
                            ++prev_len;
                        }
                    }
                }
            }
        }
        cout << len << endl;
    }
    return 0;
}
