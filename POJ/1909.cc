//Name: Marbles on a tree
//Level: 3
//Category: 動的計画法,DP,木,Tree
//Note:

/**
 * 木なので、ある頂点から他の頂点にマーブルを移すときのパスは一意である。
 * 
 * ある頂点にマーブルを持ってくる必要があるときは、その前にどこかの親ノードを経由する。
 * また、ある頂点でマーブルが余った時は、ひとつ上の親に上げる以外に選択肢はない。
 * したがって、それぞれのノードについて、
 * ・上から持ってこなければならない個数
 * ・余って下から上がってくる個数
 * を計算すると、これらの和が答えとなる。
 *
 * オーダーはO(N)。
 */
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> graph[10000];
int marbles[10000];
int need[10000];
bool is_root[10000];

int calc(int pos) {
    const int N = graph[pos].size();
    int res = 0;
    need[pos] = 1;
    for(int i = 0; i < N; ++i) {
        const int child = graph[pos][i];
        res += calc(child);
        marbles[pos] += marbles[child];
        need[pos] += need[child];
    }
    return res + abs(need[pos] - marbles[pos]);
}

bool solve() {
    int N;
    scanf("%d", &N);
    if(N == 0) return false;

    fill_n(is_root, N, true);
    for(int i = 0; i < N; ++i) {
        int v, m, d;
        scanf("%d %d %d", &v, &m, &d);
        --v;
        marbles[v] = m;
        graph[v].clear();
        while(d--) {
            int c;
            scanf("%d", &c);
            --c;
            graph[v].push_back(c);
            is_root[c] = false;
        }
    }
    int root = 0;
    while(!is_root[root]) ++root;
    printf("%d\n", calc(root));
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
