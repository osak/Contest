//Name: Provident Housewife
//Level: 2
//Category: グラフ,Graph,最短経路,ダイクストラ法,Dijkstra
//Note:

/*
 * 買い物を最小コストで行なうには，全てのスーパーの間で最小の価格でそれぞれの品物を買えば良い．
 * 最短距離を求めるためには (現在地,買った品物の組み合わせ) を状態としてダイクストラ法などで
 * (0,0) から (0,(1<<Q)-1) までの距離を求めればよい．
 * このとき，(i,p) から (i',p') に移動可能な条件は
 *   ・iからi'への道が存在する
 *   ・pにi'で買える品物群(最小コストのもののみ)を加えるとp'になる
 *
 * オーダーはそれぞれの品物の最小コストを求めるのが O(QN lg K)，ダイクストラが O((N*2^Q)*M*(lg N + lg Q))．
 * 最大ケースでは N=11, Q=15, M=N^2=121 であるからだいたい 3.5 億回くらいのループになる計算だが，全ての状態が
 * 有効なわけではない(特に N が Q より少ないため，p が2ビット以上同時に変わる場所が存在する)のでもうちょっと落ちて間に合う．
 */
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
#include <map>
#include <climits>

using namespace std;

struct Tag {
    int pos, pat, cost;
    Tag() : pos(0), pat(0), cost(0) {}
    Tag(int p, int pat, int c) : pos(p), pat(pat), cost(c) {}
    bool operator <(const Tag &other) const {
        return cost > other.cost;
    }
};

struct Dict {
    map<string,int> dict;
    int id;

    Dict() : id(0) {}

    int get(const string &str) {
        if(dict.count(str)) return dict[str];
        return dict[str] = id++;
    }
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        map<string,int> best_price;
        vector<map<string,int> > store(N+1);
        for(int i = 1; i <= N; ++i) {
            int K;
            cin >> K;
            while(K--) {
                string name;
                int price;
                cin >> name >> price;
                store[i][name] = price;
                if(best_price.count(name) == 0 || best_price[name] > price) {
                    best_price[name] = price;
                }
            }
        }
        int Q;
        cin >> Q;
        bool impossible = false;
        int ans_value = 0;
        vector<int> mask(N+1, 0);
        Dict dict;
        for(int i = 0; i < Q; ++i) {
            string name;
            cin >> name;
            if(best_price.count(name) == 0) {
                impossible = true;
            }
            const int id = dict.get(name);
            ans_value += best_price[name];
            for(int j = 1; j <= N; ++j) {
                if(store[j].count(name) && store[j][name] == best_price[name]) {
                    mask[j] |= (1<<id);
                }
            }
        }
        int M;
        cin >> M;
        vector<vector<pair<int,int> > > road(N+1);
        while(M--) {
            int S, T, D;
            cin >> S >> T >> D;
            road[S].push_back(make_pair(T, D));
            road[T].push_back(make_pair(S, D));
        }

        if(impossible) {
            cout << "impossible" << endl;
        } else {
            ++N;
            vector<vector<int> > memo(N, vector<int>(1<<Q, INT_MAX));
            priority_queue<Tag> q;
            q.push(Tag(0, 0, 0));
            while(!q.empty()) {
                const Tag t = q.top();
                q.pop();
                if(memo[t.pos][t.pat] < t.cost) continue;
                memo[t.pos][t.pat] = t.cost;
                if(t.pos == 0 && t.pat == (1<<Q)-1) break;

                for(vector<pair<int,int> >::const_iterator it = road[t.pos].begin(); it != road[t.pos].end(); ++it) {
                    const int npos = it->first;
                    const int npat = t.pat | mask[npos];
                    const int ncost = t.cost + it->second;
                    if(memo[npos][npat] > ncost) {
                        memo[npos][npat] = ncost;
                        q.push(Tag(npos, npat, ncost));
                    }
                }
            }
            cout << ans_value << ' ' << memo[0][(1<<Q)-1] << endl;
        }
    }
    return 0;
}
