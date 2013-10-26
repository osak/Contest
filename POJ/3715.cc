//Name: Blue and Red
//Level: 3
//Category: グラフ,Graph,辞書順最小,二部グラフ,最大独立集合,二部マッチング
//Note:

/**
 * 二部グラフ上で最大独立集合を求める問題。
 * 一般に、最大独立集合のサイズは、頂点数から最小点被覆のサイズを引いたものに等しい。
 * また、König's Theoremより、二部グラフ上での最小点被覆のサイズは最大マッチングの個数に等しい。
 * したがって、最大マッチングの個数と同じだけの頂点を除けばよいことがわかる。
 * 取り除く頂点を辞書順に出力するには、ある頂点を取り除いた時に最大マッチングの個数が減るかどうかを試し、
 * 減るならばその頂点を本当に取り除く、ということを先頭から順に行えば良い。
 *
 * オーダーは O(N(N+M))。
 */
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int color[200];
vector<int> graph[200];
bool visited[200];
bool eliminated[200];
int match_to[200];
int N;

bool augment(int pos) {
    if(pos == -1) return true;
    const int N = graph[pos].size();
    for(int i = 0; i < N; ++i) {
        const int neigh = graph[pos][i];
        if(eliminated[neigh]) continue;
        if(visited[neigh]) continue;
        visited[neigh] = true;
        if(augment(match_to[neigh])) {
            match_to[neigh] = pos;
            return true;
        }
    }
    return false;
}

int bm() {
    fill_n(match_to, N, -1);
    int res = 0;
    for(int i = 0; i < N; ++i) {
        if(color[i] == 0 && !eliminated[i]) {
            fill_n(visited, N, false);
            if(augment(i)) ++res;
        }
    }
    return res;
}

bool solve() {
    int M;
    scanf("%d %d", &N, &M);
    fill_n(eliminated, N, false);
    for(int i = 0; i < N; ++i) {
        scanf("%d", &color[i]);
        graph[i].clear();
    }
    for(int i = 0; i < M; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        if(color[a] != color[b]) {
            if(color[a] == 0) graph[a].push_back(b);
            else graph[b].push_back(a);
        }
    }
    int to_elim = bm();
    printf("%d", to_elim);
    for(int i = 0; i < N; ++i) {
        eliminated[i] = true;
        if(bm() == to_elim-1) {
            printf(" %d", i);
            to_elim--;
        } else {
            eliminated[i] = false;
        }
    }
    puts("");
    return true;
}

int main() {
    int N;
    scanf("%d", &N);
    while(N--) solve();
    return 0;
}
