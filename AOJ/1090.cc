//Name: Sports Days
//Level: 5
//Category: グラフ,Graph,k-最短路
//Note:

/*
 * 問題を整理すると以下のようになる．
 * ・負辺，閉路を含み得る有向グラフが与えられる．
 * ・各頂点にはラベルが付けられており，特定の順序でラベルを辿ることは禁止される．
 * ・スタートからゴールまでのパスを短い方から最大K本見つける．
 * ・最短パスがいくらでもコストを下げられる場合も検出する．
 *
 * まず，禁止順序の処理はKMP法と同様のオートマトンを作成することで可能である．
 * オートマトンのある状態からの失敗遷移は，文字列を1文字遅れで読んでいくカーソルからの失敗遷移と等しくなる（証明略）．
 *
 * 次に，最初に与えられた頂点vをオートマトンの頂点数pと同じだけ複製し，頂点(v,p)に関してグラフを作成する．
 * 以降はこのグラフに関して問題を考えれば良くなる．
 *
 * 最短パスがいくらでもコストを下げられる状態は，負閉路が存在してかつゴールまで到達可能な場合である．
 * Bellman-Fordを使い，最初に頂点数の回数だけrelaxしてから更に同じ回数だけrelaxしたとき，ゴールのコストが更新された場合は
 * ゴールに到達可能な負閉路があるとしてよい．
 *
 * 最後にk-最短路を求める．
 * これは各頂点に対し，最もコストの低いK個のコストだけを覚えておき，これ以上のコストで遷移してきた場合は弾くようにすることで達成できる．
 * ただし通常のBellman-Fordでは直前に更新された状態とそれより前のメモの区別が付けられないので，適宜工夫する．
 *
 * オーダーは禁止パターンの長さをPとして
 * ・頂点数が |V| = N * P
 * ・辺数が |E| = O(MP)
 * ・Bellman-Fordが O(|V||E|) = O(NMP^2)
 * ・Bellman-Fordの更新1回につき O(P)
 * より，全体では O(NMP^3) となる．
 */
//#define _GLIBCXX_DEBUG
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <deque>
#include <algorithm>
#include <cassert>

using namespace std;

#define FOREACH(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define TIMES(i,n) for(int i = 0; i < (n); ++i)

typedef long long Cost;
const long long INF = 1000*1000*10*10*2*10LL;

struct Edge {
    int from, to;
    Cost cost;

    Edge() {}
    Edge(int f, int t, Cost c) : from(f), to(t), cost(c) {}
};

struct DistTag {
    int size;
    deque<Cost> buf, newbie;

    DistTag(int size) : size(size), buf(size, INF) {
        //newbie.reserve(size);
    }

    bool insert(Cost val) {
        if(buf.back() <= val) return false;
        deque<Cost>::iterator ins_pos = upper_bound(newbie.begin(), newbie.end(), val);
        newbie.insert(ins_pos, val);
        if(static_cast<int>(newbie.size()) > size) newbie.pop_back();
        return true;
    }

    bool has(Cost val) {
        return buf.back() >= val;
    }

    void flush() {
        FOREACH(it, newbie) {
            deque<Cost>::iterator ins_pos = upper_bound(buf.begin(), buf.end(), *it);
            buf.insert(ins_pos, *it);
        }
        buf.resize(size);
        newbie.clear();
    }
};

struct State {
    int pos;
    Cost cost;

    State() {}
    State(int p, Cost c) : pos(p), cost(c) {}

    bool operator <(const State &other) const {
        return cost > other.cost; // Reversed
    }
};

typedef vector<Edge> EdgeList;

void check_reachable(int start, const vector<EdgeList> &graph, vector<unsigned char> &reachable) {
    queue<int> q;
    q.push(start);
    reachable[start] = 1;
    while(!q.empty()) {
        int cur = q.front();
        q.pop();
        FOREACH(it, graph[cur]) {
            if(!reachable[it->to]) {
                reachable[it->to] = 1;
                q.push(it->to);
            }
        }
    }
}

bool relax(const vector<EdgeList> &graph, vector<Cost> &dist) {
    bool updated = false;
    FOREACH(list_it, graph) {
        FOREACH(it, *list_it) {
            const Cost cost = dist[it->from] + it->cost;
            if(dist[it->to] > cost) {
                dist[it->to] = cost;
                updated = true;
            }
        }
    }
    return updated;
}

pair<int,Cost> search(int start, const vector<EdgeList> &graph, int N, int P, int K) {
    vector<DistTag> dist(graph.size(), DistTag(K));
    dist[start].insert(0);

    TIMES(_, static_cast<int>(graph.size())*K) {
        TIMES(i, static_cast<int>(graph.size())) {
            DistTag &dt = dist[i];
            if(dt.newbie.size() == 0) continue;
            vector<int> tmp;
            FOREACH(it, graph[i]) {
                assert(it->from == i);
                // Corner case: loop edge
                if(it->to == i) {
                    FOREACH(nit, dt.newbie) {
                        tmp.push_back(*nit + it->cost);
                    }
                } else {
                    FOREACH(nit, dt.newbie) {
                        //cout << "insert " << i << ' ' << it->to << endl;
                        dist[it->to].insert(*nit + it->cost);
                    }
                }
            }
            dt.flush();
            FOREACH(tit, tmp) {
                dt.insert(*tit);
            }
        }
    }
    pair<int,Cost> res(0, 0);
    vector<Cost> costs;
    TIMES(i, P) {
        FOREACH(it, dist[(N-1)*P+i].buf) {
            costs.push_back(*it);
        }
    }
    sort(costs.begin(), costs.end());
    TIMES(i, min(K, static_cast<int>(costs.size()))) {
        if(costs[i] == INF) break;
        res.first++;
        res.second += costs[i];
    }
    return res;
}

pair<int,Cost> solve(int N) {
    vector<int> color_of(N);
    TIMES(i, N) {
        cin >> color_of[i];
        --color_of[i];
    }
    int M;
    cin >> M;
    vector<Edge> edges(M);
    TIMES(i, M) {
        Edge &e = edges[i];
        cin >> e.from >> e.to >> e.cost;
        --e.from; --e.to;
    }
    int K;
    cin >> K;
    vector<int> prohibited;
    {
        string str;
        cin >> str;
        FOREACH(it, str) {
            prohibited.push_back(*it - '0' - 1);
        }
    }
    const int P = prohibited.size();
    vector<vector<int> > next_prohibited_pos(P, vector<int>(4, 0));
    {
        int shadow = 0;
        TIMES(i, P) {
            next_prohibited_pos[i][prohibited[i]] = i+1;
            if(i > 0) {
                TIMES(j, 4) {
                    if(j != prohibited[i]) next_prohibited_pos[i][j] = next_prohibited_pos[shadow][j];
                }
                shadow = next_prohibited_pos[shadow][prohibited[i]];
            }
        }
    }

    const int start = 0+next_prohibited_pos[0][color_of[0]];
    vector<EdgeList> graph(N*P);
    FOREACH(it, edges) {
        TIMES(i, P) {
            // Cannot reach this state.
            if(i > 0 && prohibited[i-1] != color_of[it->from]) continue;

            int np = next_prohibited_pos[i][color_of[it->to]];
            if(np < P) {
                graph[it->from*P+i].push_back(Edge(it->from*P+i, it->to*P+np, it->cost));
                //cout << it->from << ' ' << i << ' ' << it->to << ' ' << np << endl;
            }
        }
    }

    // Remove all unreachable nodes.
    // It causes fake negative loop detection.
    vector<unsigned char> reachable(N*P, 0);
    check_reachable(start, graph, reachable);
    TIMES(i, N*P) {
        if(!reachable[i]) graph[i].clear();
    }

    // Check if it has negative loop
    vector<Cost> dist(N*P, INF);
    dist[start] = 0;
    TIMES(_, N*P) {
        relax(graph, dist);
    }
    vector<Cost> tmp_last(P);
    TIMES(i, P) {
        tmp_last[i] = dist[(N-1)*P+i];
    }
    TIMES(_, N*P) {
        relax(graph, dist);
        TIMES(i, P) {
            if(dist[(N-1)*P+i] != tmp_last[i]) return make_pair(-1, -1);
        }
    }

    // Corner case: cannot start
    if(P == 1 && prohibited[0] == color_of[0]) return make_pair(0, 0);

    pair<int,Cost> res = search(start, graph, N, P, K);
    return res;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int N;
    while(cin >> N) {
        if(!N) break;
        pair<int,Cost> ans = solve(N);
        if(ans.first == -1) cout << -1 << endl;
        else cout << ans.first << ' ' << ans.second << endl;
    }
    return 0;
}
