#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Girl {
    int param[3];
    int entropy;
};

struct Tag {
    int score;
    vector<Girl const*> v;

    Tag() : score(0) {}

    void add(Girl const *g) {
        if(g->entropy > 0) return;
        v.push_back(g);
        score += g->entropy;
    }

    Girl const* get(int idx) const {
        return v[idx];
    }

    int size() const { 
        return v.size();
    }

    void clear() {
        score = 0;
        v.clear();
    }
};

void gen_group(const Tag &v, int pindex, int lim, int threshold, vector<Tag> &ret) {
    ret.clear();
    vector<int> used(1001, 0);

    Tag t;
    for(int i = 0; i < v.size(); ++i) {
        int minval = v.get(i)->param[pindex];
        if(used[minval]) continue;
        used[minval] = true;

        t.clear();
        for(int j = 0; j < v.size(); ++j) {
            Girl const* g = v.get(j);
            if(g->param[pindex] >= minval && g->param[pindex] - minval <= lim) t.add(g);
        }
        if(t.score < threshold) ret.push_back(t);
    }
}

int main() {
    ios::sync_with_stdio(0);

    int N;
    while(cin >> N) {
        Tag init;

        for(int j = 0; j < N; ++j) {
            Girl *g = new Girl();
            for(int i = 0; i < 3; ++i) cin >> g->param[i];
            cin >> g->entropy;
            init.add(g);
        }

        int B, W, H;
        cin >> B >> W >> H;

        vector<Tag> b, w, h;
        vector<Tag> tmp;
        int ans = 0;

        gen_group(init, 0, B, ans, b);
        for(int i = 0; i < b.size(); ++i) {
            //cout << i << '/' << b.size() << endl;
            if(b[i].score >= ans) continue;
            w.clear();
            gen_group(b[i], 1, W, ans, w);

            for(int k = 0; k < w.size(); ++k) {
                if(w[k].score >= ans) continue;
                h.clear();
                gen_group(w[k], 2, H, ans, h);
                for(int j = 0; j < h.size(); ++j) {
                    ans = min(ans, h[j].score);
                }
            }
        }

        if(ans >= 0) cout << "Error 404, mahou shoujo not found!" << endl;
        else cout << ans << endl;
    }

    return 0;
}
