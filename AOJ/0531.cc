#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <set>

using namespace std;

struct Mask {
    int x1, x2, y1, y2;
};

struct Tag {
    int pos, idx;
    bool isStart;
    Tag() {}
    Tag(int p, int id, bool s) : pos(p), idx(id), isStart(s) {}
};

struct Area {
    int start, end;
    int color;
};

bool operator < (const Mask &m1, const Mask &m2) {
    if(m1.x1 != m2.x1) return m1.x1 < m2.x1;
    return m1.y1 < m2.y1;
}

bool operator < (const Tag &t1, const Tag &t2) {
    if(t1.pos == t2.pos) return !t1.isStart && t2.isStart;
    return t1.pos < t2.pos;
}

bool operator == (const Tag &t1, const Tag &t2) {
    return t1.pos == t2.pos;
}

//Verified PKU 2524
int getroot(int i, vector<int> &roots, const vector<int> &levels) {
    if(roots[i] == i) return i;
    else return (roots[i] = getroot(roots[i], roots, levels));
}

//Verified PKU 2524
bool unite(int i, int j, vector<int> &roots, vector<int> &levels) {
    i = getroot(i, roots, levels);
    j = getroot(j, roots, levels);
    if(i == j) return false;

    if(levels[i] < levels[j]) {
        roots[i] = j;
    }
    else {
        roots[j] = i;
        if(levels[i] == levels[j]) ++levels[i];
    }
    return true;
}

int main() {
    while(true) {
        int W, H;
        cin >> W >> H;
        if(!W && !H) break;

        int N;
        cin >> N;
        vector<Mask> masks;
        vector<Tag> tags_x, tags_y;
        for(int i = 0; i < N; ++i) {
            Mask m;
            cin >> m.x1 >> m.y1 >> m.x2 >> m.y2;
            masks.push_back(m);
            tags_x.push_back(Tag(m.x1, i, true));
            tags_x.push_back(Tag(m.x2, i, false));
            tags_y.push_back(Tag(m.y1, i, true));
            tags_y.push_back(Tag(m.y2, i, false));
        }
        Mask m;
        m.y1 = -1;
        m.y2 = H+1;
        masks.push_back(m);
        tags_x.push_back(Tag(0, masks.size()-1, false));
        tags_x.push_back(Tag(W, masks.size()-1, true));
        tags_y.push_back(Tag(0, 1000, false));
        tags_y.push_back(Tag(H, 1000, true));
        sort(tags_x.begin(), tags_x.end());
        sort(tags_y.begin(), tags_y.end());
        tags_y.erase(unique(tags_y.begin(), tags_y.end()), tags_y.end());

        int colorcnt = 0;
        vector<int> colorvec(50000);
        vector<int> levels(50000, 0);
        for(int i = 0; i < 50000; ++i) {
            colorvec[i] = i;
            levels[i] = i;
        }

        vector<Area> active;
        for(int i = 0; i < tags_y.size()-1; ++i) {
            //cout << tags_y[i].pos << ' ' << tags_y[i].isStart << ' ' << colorcnt << endl;
            int sy = tags_y[i].pos, ey = tags_y[i+1].pos;
            Area curr;
            curr.start = 0;
            curr.color = 0;
            vector<Area> currRow;
            int inWall = 0;
            for(int j = 0; j < tags_x.size(); ++j) {
                Mask m = masks[tags_x[j].idx];
                if(ey <= m.y1 || m.y2 <= sy) continue;
                if(tags_x[j].isStart) {
                    if(inWall) continue;
                    ++inWall;
                    curr.end = tags_x[j].pos;
                    if(curr.start == curr.end) continue;

                    curr.color = ++colorcnt;
                    for(int k = 0; k < active.size(); ++k) {
                        if(!(active[k].start >= curr.end || active[k].end <= curr.start))
                        {
                        //    printf("\t(%d %d), (%d %d)\n", active[k].start, active[k].end, curr.start, curr.end);
                            unite(active[k].color, curr.color, colorvec, levels);
                        }
                    }
                    //if(curr.color == 0) {
                    //    printf("\t(%d %d)\n", curr.start, curr.end);
                    //}
                    currRow.push_back(curr);
                }
                else {
                    if(inWall == 0 || !--inWall) {
                        curr.start = tags_x[j].pos;
                        curr.color = 0;
                    }
                }
            }
            active = currRow;
        }

        set<int> ans;
        for(int i = 1; i <= colorcnt; ++i) {
            ans.insert(getroot(i, colorvec, levels));
        }
        if(ans.size() == 0) cout << 1 << endl;
        else cout << ans.size() << endl;
    }
    return 0;
}
