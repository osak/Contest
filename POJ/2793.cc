//Name: Cactus
//Level: 3
//Category: グラフ,Graph,ループ検出,多倍長,Bigint
//Note:

/*
 * ループ検出は使ったことのない辺をたどっていく深さ優先探索し，訪問済み頂点にたどりついたら履歴をたどることで可能．
 * 同じ辺が複数のループに使われてはいけないという条件があるため，この条件を破った瞬間にDFSを止めるようにすると，この操作は O(M) で完了する．
 * 各ループについては高々1本までの辺を抜いてもCactusであることは簡単にわかるから，それを全て掛け合わせればよい．
 * 答えは long long にも収まらない可能性があることに注意(三角形がたくさん繋がったグラフなど)．
 *
 * オーダーは O(M)．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
#include <utility>

using namespace std;

struct Bigint {
    vector<int> digits;

    Bigint() {
        digits.push_back(1);
    }

    Bigint& operator *=(int n) {
        int carry = 0;
        const int N = digits.size();
        for(int i = 0; i < N; ++i) {
            digits[i] *= n;
            digits[i] += carry;
            carry = digits[i] / 10;
            digits[i] %= 10;
        }
        while(carry > 0) {
            digits.push_back(carry % 10);
            carry /= 10;
        }
        return *this;
    }

    friend ostream& operator <<(ostream &o, const Bigint &b) {
        for(vector<int>::const_reverse_iterator it = b.digits.rbegin(); it != b.digits.rend(); ++it) {
            o << *it;
        }
        return o;
    }
};

struct Edge {
    int to;
    int loopcnt;
    bool visited;
    Edge *other;

    Edge() : loopcnt(0), visited(false) {}
    explicit Edge(int t) : to(t), loopcnt(0), visited(false) {}

    void visit() {
        visited = other->visited = true;
    }

    void markloop() {
        ++loopcnt;
        ++other->loopcnt;
    }
};

Edge edgebuf[1000*1000];
int edgebuf_ptr = 0;
Edge* make_edge(int t) {
    Edge *e = &edgebuf[edgebuf_ptr++];
    e->to = t;
    return e;
}

vector<vector<Edge*> > graph;
vector<int> loops;
vector<pair<int,Edge*> > history;
vector<unsigned char> visited;

void dfs(int pos) {
    if(visited[pos]) {
        int len = 1;
        int cur = (int)history.size() - 1;
        while(history[cur].first != pos) {
            //cout << history[cur].first << endl;
            if(history[cur].second->loopcnt > 0) throw "Not a cactus";
            history[cur].second->markloop();
            //cout << "Mark " << history[cur].first << " to " << history[cur].second->to << endl;
            --cur;
            ++len;
        }
        if(history[cur].second->loopcnt > 0) throw "Not a cactus";
        history[cur].second->markloop();
        //cout << "-" << endl;
        loops.push_back(len);
    } else {
        visited[pos] = 1;
        vector<Edge*> &edges = graph[pos];
        const int N = edges.size();
        for(int i = 0; i < N; ++i) {
            if(edges[i]->visited) continue;
            edges[i]->visit();
            history.push_back(make_pair(pos, edges[i]));
            dfs(edges[i]->to);
            history.pop_back();
        }
    }
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    graph.resize(N);
    visited.resize(N, 0);
    while(M--) {
        int K;
        scanf("%d", &K);
        int prev = -1;
        while(K--) {
            int v;
            scanf("%d", &v);
            --v;
            if(prev != -1) {
                Edge *a = make_edge(v), *b = make_edge(prev);
                a->other = b;
                b->other = a;
                graph[prev].push_back(a);
                graph[v].push_back(b);
            }
            prev = v;
        }
    }

    try {
        dfs(0);
        for(int i = 0; i < N; ++i) {
            if(!visited[i]) {
                throw "Not connected";
            }
        }
        Bigint ans;
        for(vector<int>::const_iterator it = loops.begin(); it != loops.end(); ++it) {
            ans *= (*it)+1;
        }
        cout << ans << endl;
    } catch (const char *msg) {
        cout << 0 << endl;
    }

    return 0;
}
