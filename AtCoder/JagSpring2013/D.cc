//Name: Medical Inspection
//Level: 5
//Category: 探索
//Note:

/*
 * ノードを次数の高い順に見ていき，使うか使わないかを決めていく．
 * 求めるのは点被覆であり，ある辺を被覆するには両端の少なくともどちらかの頂点を使わなければならないから，
 * あるノードに対し
 * ・使うとき→接続しているノードの次数を1減らす（辺の削除に対応）
 * ・使わないとき→接続しているノードを全て使う
 * という操作が可能になる．
 * また，自明な枝刈りとして
 * ・使っている頂点数が現時点での最小頂点数かKを超えたら打ち切り
 * を入れる．
 *
 * ただし，これだけだと全て次数が2の輪っかなどでTLEしてしまうため，枝刈りとして
 * ・次数が1の頂点は無条件で使わないようにする
 * を入れると解ける．
 */
#include <iostream>
#include <bitset>
#include <vector>
#include <algorithm>

using namespace std;

typedef bitset<3000> Flag;

int ans = 30000;
int K;
int use_it(int pos, const vector<Flag> &graph, vector<int> &degree, Flag &used) {
    const int N = graph.size();
    int cnt = 0;
    for(int i = 0; i < N; ++i) {
        if(graph[pos][i] && !used[i]) {
            --degree[i];
            ++cnt;
        }
    }
    degree[pos] = 0;
    used.set(pos);
    return cnt;
}

void dfs(int pos, const vector<Flag> &graph, vector<int> &degree, const vector<int> &ord, const Flag &used, int rem) {
    const int cur = used.count();
    if(cur > K) return;
    if(cur >= ans) return;
    const int N = graph.size();
    const vector<int> org_deg(degree);
    const int node = ord[pos];
    //cout << pos << ' ' << used << ' ' << rem << endl;
    if(pos == N) {
        if(rem == 0) {
            ans = min(ans, (int)used.count());
        }
    } else if(!used[node]) {
        // Use this node
        if(degree[node] > 1) {
            Flag next(used);
            int removed = use_it(node, graph, degree, next);
            dfs(pos+1, graph, degree, ord, next, rem-removed);
            degree = org_deg;
        }
        // Not use this node
        {
            Flag next(used);
            int removed = 0;
            for(int i = 0; i < N; ++i) {
                if(graph[node][i] && !next[i]) {
                    removed += use_it(i, graph, degree, next);
                }
            }
            dfs(pos+1, graph, degree, ord, next, rem-removed);
            degree = org_deg;
        }
    } else {
        dfs(pos+1, graph, degree, ord, used, rem);
    }
}

struct Cmp {
    vector<int> degree;
    Cmp(const vector<int> &v) : degree(v) {}

    bool operator ()(int a, int b) const {
        return degree[a] < degree[b];
    }
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int N, M;
    cin >> N >> M >> K;

    vector<int> degree(N, 0);
    vector<Flag> graph(N);
    for(int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        graph[a].set(b);
        graph[b].set(a);
        degree[a]++;
        degree[b]++;
    }
    vector<int> ord(N);
    for(int i = 0; i < N; ++i) ord[i] = i;
    sort(ord.begin(), ord.end(), Cmp(degree));
    reverse(ord.begin(), ord.end());

    dfs(0, graph, degree, ord, Flag(), M);
    if(ans > N) cout << "Impossible" << endl;
    else cout << ans << endl;
    return 0;
}
