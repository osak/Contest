#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <climits>

using namespace std;

struct Tag {
    int cost;
    int pos;
    vector<int> threaten;

    Tag(int N) : threaten(vector<int>(N, 0)) {}
    Tag(int N, int c, int p) : threaten(vector<int>(N, 0)), cost(c), pos(p) {}
    Tag(const Tag &other) : threaten(other.threaten) {}
};

int main() {
    int T;
    cin >> T;
    for(int CASE = 1; CASE <= T; ++CASE) {
        int P, W;
        vector<vector<int> > v(P, vector<int>(P, 0));
        for(int i = 0; i < W; ++i) {
            char comma;
            int a, b;
            cin >> a >> comma >> b;
            v[a][b] = v[b][a] = 1;
        }

        int mincost = INT_MAX;
        int threat = 0;
        queue<Tag> q;
        Tag t(P, 0, 0);
        for(int i = 0; i < P; ++i)
            if(v[0][i]) t.threaten[i] = 1;
        q.push(t);
        while(!q.empty()) {
            Tag &t = q.front();
            q.pop();

            if(mincost < INT_MAX) {
                if(t.cost > mincost) break;
                int tcnt = 0;
                for(int i = 0; i < P; ++i)
                    if(t.threaten[i]) ++tcnt;
                threat = max(threat, tcnt);
            }

            for(int i = 0; i
