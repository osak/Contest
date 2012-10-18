//Name: Consistent Unit System
//Level: 3
//Category: グラフ,Graph
//Note:

/*
 * 有向グラフをつくって，それぞれの連結なグラフごとにどこかを始点として
 * 各単位の相対的な指数を計算し，矛盾が生じるかどうか確かめる．
 * 矛盾が生じるとは，一度決まった数値と違う数値で更新されることである．
 *
 * 頂点数は最大で 2N であることに注意．
 *
 * 以下はDFSによる実装．オーダーは O(N^2) 程度．
 */
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>
#include <queue>

using namespace std;

const int INF = 200*100 + 100;

struct Dict {
    map<string,int> dict;
    int id;

    Dict() : id(0) {}

    int get(const string &str) {
        if(dict.count(str)) return dict[str];
        return dict[str] = id++;
    }

    int size() const { return id; }
};

bool dfs(int pos, int val, const vector<vector<pair<int,int> > > &graph, vector<int> &dist) {
    if(dist[pos] != INF) return dist[pos] == val;
    dist[pos] = val;
    const vector<pair<int,int> > &edges = graph[pos];
    for(vector<pair<int,int> >::const_iterator it = edges.begin(); it != edges.end(); ++it) {
        int nc = val + it->second;
        if(!dfs(it->first, nc, graph, dist)) return false;
    }
    return true;
}

vector<vector<pair<int,int> > > v(200);
vector<int> dist(200);
vector<unsigned char> visited(200);

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    while(true) {
        int N;
        cin >> N;
        if(!N) break;
        cin.ignore();
        for(int i = 0; i < 2*N; ++i) {
            v[i].clear();
        }
        Dict dict;
        for(int i = 0; i < N; ++i) {
            string line;
            getline(cin, line);
            for(string::iterator it = line.begin(); it != line.end(); ++it) {
                if(*it == '=' || *it == '^') *it = ' ';
            }
            istringstream is(line);
            string unit_left, unit_right;
            int ord;
            int tmp;
            is >> tmp >> unit_left >> tmp >> ord >> unit_right;
            //sscanf(line.c_str(), "%*d %s = %*d^%d %s ", unit_left, &ord, unit_right);
            const int id_left = dict.get(string(unit_left));
            const int id_right = dict.get(string(unit_right));
            v[id_left].push_back(make_pair(id_right, ord));
            v[id_right].push_back(make_pair(id_left, -ord));
        }

        const int M = dict.size();
        bool ok = true;
        fill(dist.begin(), dist.end(), INF);
        for(int i = 0; i < M; ++i) {
            if(dist[i] == INF) {
                if(!dfs(i, 0, v, dist)) {
                    ok = false;
                    break;
                }
            }
        }

        if(!ok) {
            cout << "No" << endl;
        } else {
            cout << "Yes" << endl;
        }
    }
    return 0;
}
