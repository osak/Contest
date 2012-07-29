#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

struct Tag {
    int a, b;
    int w;

    bool operator < (const Tag &other) const {
        return w < other.w;
    }
};

//Verified PKU 2524
int getroot(int i, vector<int> &roots) {
    if(roots[i] == i) return i;
    else return (roots[i] = getroot(roots[i], roots));
}

//Verified PKU 2524
bool unite(int i, int j, vector<int> &roots, vector<int> &levels) {
    i = getroot(i, roots);
    j = getroot(j, roots);
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
        int N, M;
        cin >> N >> M;
        if(!N && !M) break;

        vector<Tag> v;

        for(int i = 0; i < M; ++i) {
            Tag t;
            cin >> t.a >> t.b >> t.w;
            v.push_back(t);
        }

        sort(v.begin(), v.end());

        int ans = INT_MAX;
        if(v.size() < N-1) {
            ans = -1;
            goto next;
        }

        for(int start = 0; start < v.size(); ++start) {
            int left = start-1, right = start+1;
            int cnt = 1;
            int mincost = v[start].w, maxcost = v[start].w;

            vector<int> roots(N+1), levels(N+1, 0);
            for(int i = 0; i < roots.size(); ++i) roots[i] = i;
            unite(v[start].a, v[start].b, roots, levels);

            /*
            for(cnt = 2; cnt <= N-1; ++cnt) {
                while(left >= 0 && getroot(v[left].a, roots) == getroot(v[left].b, roots)) --left;
                while(right < v.size() && getroot(v[right].a, roots) == getroot(v[right].b, roots)) ++right;

                int dl = INT_MAX, dr = INT_MAX;
                if(left >= 0) {
                    dl = maxcost - v[left].w;
                }
                if(right < v.size()) {
                    dr = v[right].w - mincost;
                }

                if(dl < dr) {
                    mincost = v[left].w;
                    unite(v[left].a, v[left].b, roots, levels);
                }
                else if(dr != INT_MAX) {
                    maxcost = v[right].w;
                    unite(v[right].a, v[right].b, roots, levels);
                }
                else {
                    ans = -1;
                    goto next;
                }
            }
            */
            cnt = 1;
            for(int i = start+1; i < v.size(); ++i) {
                if(getroot(v[i].a, roots) == getroot(v[i].b, roots)) continue;
                //cout << "Connect " << v[i].a << ' ' << v[i].b << endl;
                unite(v[i].a, v[i].b, roots, levels);
                mincost = min(mincost, v[i].w);
                maxcost = max(maxcost, v[i].w);
                ++cnt;
            }
            if(cnt == N-1) {
                //cout << "Cost: " << maxcost-mincost << endl << endl;
                ans = min(ans, maxcost-mincost);
            }
            else {
                //cout << "Not spanning" << endl << endl;
            }
        }
next:
        if(ans == INT_MAX) ans = -1;
        cout << ans << endl;
    }

    return 0;
}
