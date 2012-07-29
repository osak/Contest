#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cassert>

using namespace std;

struct Tag {
    int t, n, pos;

    Tag() {}
    Tag(int t, int n, int p) : t(t), n(n), pos(p) {}

    bool operator < (const Tag &other) const {
        return t > other.t;
    }
};

vector<int> speed;
bool speedcmp(const Tag &t1, const Tag &t2) {
    return speed[t1.n] < speed[t2.n];
}

int main() {
    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        speed.resize(N);
        vector<int> lap(N, 0);
        for(int i = 0; i < N; ++i) {
            cin >> speed[i] >> lap[i];
            lap[i] *= 2;
        }

        int ans = 0;
        vector<int> nt(2, 0);
        priority_queue<Tag> q;
        for(int i = 0; i < N; ++i) {
            q.push(Tag(0, i, 0));
        }
        while(!q.empty()) {
            Tag t = q.top();
            q.pop();

            ans = t.t;
            vector<Tag> v;
            v.push_back(t);
            while(!q.empty() && q.top().t == t.t) {
                v.push_back(q.top());
                q.pop();
            }
            sort(v.begin(), v.end(), speedcmp);
            for(int i = 0; i < v.size(); ++i) {
                const Tag &tag = v[i];
                //cout << tag.t << ' ' << tag.n << ' ' << tag.pos << endl;
                if(i > 0) assert(speed[tag.n] >= speed[v[i-1].n]);
                if(lap[tag.n] == 0) continue;

                int next = tag.t + speed[tag.n];
                int np = 1-tag.pos;
                if(nt[np] > next) next = nt[np];
                nt[np] = next;
                q.push(Tag(next, tag.n, np));
                lap[tag.n]--;
            }
        }

        cout << ans << endl;
    }

    return 0;
}
