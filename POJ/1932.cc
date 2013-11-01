//Name: XYZZY
//Level: 2
//Category: グラフ,Graph,幅優先探索,BFS
//Note:

/**
 * 部屋数N部屋に対して、エネルギーは100N+1あれば確実に足りる（ゴールへのパスが存在すれば）。
 * よって、部屋とエネルギーの組み合わせに対し、到達可能かを記録しながら幅優先探索すればよい。
 *
 * オーダーはO(N^2 M)。
 * ただし、Mは1つの頂点から出ている辺の本数（の最大値）。
 */
#include <cstdio>
#include <vector>

using namespace std;

int energy[100];
vector<int> graph[100];
bool reachable[100][10002];

bool solve() {
    int N;
    scanf("%d", &N);
    if(N == -1) return false;
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < 10002; ++j) {
            reachable[i][j] = false;
        }
        graph[i].clear();

        int M;
        scanf("%d %d", energy+i, &M);
        while(M--) {
            int to;
            scanf("%d", &to);
            graph[i].push_back(to-1);
        }
    }
    vector<pair<int,int> > q[2];
    q[0].push_back(make_pair(0, 100));
    reachable[0][100] = true;
    bool winnable = false;
    while(q[0].size() > 0) {
        const int M = q[0].size();
        q[1].clear();
        for(int i = 0; i < M; ++i) {
            const int cur_room = q[0][i].first;
            const int cur_energy = q[0][i].second;
            if(cur_room == N-1) {
                winnable = true;
                goto end;
            }
            const int R = graph[cur_room].size();
            for(int j = 0; j < R; ++j) {
                const int next_room = graph[cur_room][j];
                int next_energy = cur_energy + energy[next_room];
                if(next_energy <= 0) continue;
                if(next_energy > 10001) next_energy = 10001;
                if(!reachable[next_room][next_energy]) {
                    reachable[next_room][next_energy] = true;
                    q[1].push_back(make_pair(next_room, next_energy));
                }
            }
        }
        q[0].swap(q[1]);
    }
end:
    puts(winnable ? "winnable" : "hopeless");
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
