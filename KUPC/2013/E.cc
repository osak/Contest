#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int M, S, G;
vector<int> dice(6);
vector<int> field;
vector<vector<int> > graph, reversed;
vector<int> dist;

inline int edge_idx(int face, int dir) {
    if(dir == 1) return face;
    else return 6+face;
}

void build_graph() {
    graph.resize(M);
    reversed.resize(M);
    for(int i = 0; i < M; ++i) {
        graph[i].resize(12, -1);
    }

    for(int i = 0; i < M; ++i) {
        for(int dir = -1; dir <= 1; dir += 2) {
            for(int face = 0; face < 6; ++face) {
                const int step = dice[face];
                const int next = i + step*dir;
                if(0 <= next && next < M) {
                    const int to = next + field[next];
                    const int idx = edge_idx(face, dir);
                    graph[i][idx] = to;
                    reversed[to].push_back(i);
                }
            }
        }
    }
    for(auto &v : reversed) {
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
    }
}

void build_distance() {
    dist.resize(M, M);
    queue<int> q;
    q.push(G);
    dist[G] = 0;
    while(!q.empty()) {
        const int cur = q.front();
        q.pop();
        for(auto to : reversed[cur]) {
            if(dist[to] > dist[cur]+1) {
                dist[to] = dist[cur]+1;
                q.push(to);
            }
        }
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin >> M;
    for(int i = 0; i < 6; ++i) {
        cin >> dice[i];
    }
    cin >> S >> G;
    --S; --G;
    field.resize(M);
    for(int i = 0; i < M; ++i) {
        cin >> field[i];
    }

    build_graph();
    build_distance();
    /*
    for(auto i : dist) {
        cout << i << ' ';
    }
    cout << endl;
    */

    int pos = S;
    for(int _ = 0; _ < 3000; ++_) {
        int face;
        cin >> face;
        --face;
        int action = 0;
        for(int dir = -1; dir <= 1; dir += 2) {
            const int idx = edge_idx(face, dir);
            const int next = graph[pos][idx];
            if(next != -1 && dist[next] < dist[pos]) {
                action = dir;
                pos = next;
                break;
            }
        }
        cout << action << endl;
        if(pos == G) break;
    }
    return 0;
}
