//Name: The Domino Principle
//Level: 2
//Cateogry: グラフ,Graph,幅優先探索,BFS
//Note:

/**
 * それぞれのノードを始点として幅優先探索し、すべてのノードに到達できるかと
 * 最も深いノードの深さを求めればよい。
 *
 * オーダーはO(N(N+M))
 * ただしMは辺数。
 */
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int N;
vector<int> graph[1000];

int check(int start) {
    static vector<int> q[2];
    static bool visited[1000];
    fill_n(visited, N, false);
    q[0].clear();
    q[0].push_back(start);
    visited[start] = true;
    int cnt = 1;
    int turn = -1;
    while(q[0].size() > 0) {
        ++turn;
        const int M = q[0].size();
        q[1].clear();
        for(int i = 0; i < M; ++i) {
            const int cur = q[0][i];
            const int K = graph[cur].size();
            for(int j = 0; j < K; ++j) {
                const int next = graph[cur][j];
                if(!visited[next]) {
                    ++cnt;
                    visited[next] = true;
                    q[1].push_back(next);
                }
            }
        }
        q[0].swap(q[1]);
    }
    if(cnt != N) return -1;
    return turn;
}

int main() {
    scanf("%d", &N);
    for(int i = 0; i < N; ++i) {
        int D;
        scanf("%d", &D);
        while(D--) {
            int n;
            scanf("%d", &n);
            graph[i].push_back(n-1);
        }
    }
    int ans_len = -1;
    int ans_pos = 0;
    for(int i = N-1; i >= 0; --i) {
        int l = check(i);
        if(l > ans_len) {
            ans_len = l;
            ans_pos = i;
        }
    }
    if(ans_len == -1) {
        puts("impossible");
    } else {
        printf("%d\n%d\n", ans_len, ans_pos+1);
    }
    return 0;
}
