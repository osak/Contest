//Name: Wrought Gold Master
//Level: 2
//Category: グラフ,有向グラフ,Warshall-Floyd
//Note:

/*
 * 錬成の関係は有向グラフとなっている．
 * また，錬成関係はループを含む場合がある．
 *
 * したがって，有向グラフ上でWarshall-Floydのようにして，各ノードのコストをそのまま買うか錬成するかの安いほうに
 * 更新する操作を繰り替えせばよい．
 * Warshall-Floydと同様，最適解ではある材料を錬成するために必要なパス長はNを超えず，また負閉路も持たないため
 * N回以内には必ず停止することが分かる．
 *
 * オーダーはO(NM)．
 */
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;
typedef unsigned long long ULL;

struct Dict {
    map<string,int> dict;
    int id;
    Dict() : id(0) {}

    int get(const string &name) {
        if(dict.count(name)) return dict[name];
        return dict[name] = id++;
    }
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        Dict dict;
        vector<ULL> price(N);
        vector<vector<int> > materials(N);
        for(int i = 0; i < N; ++i) {
            string name;
            int p;
            cin >> name >> p;
            price[dict.get(name)] = p;
        }
        int M;
        cin >> M;
        for(int i = 0; i < M; ++i) {
            string to;
            cin >> to;
            const int to_id = dict.get(to);
            int cnt;
            cin >> cnt;
            while(cnt--) {
                string material;
                cin >> material;
                materials[to_id].push_back(dict.get(material));
            }
        }
        vector<ULL> memo(price);
        while(true) {
            bool updated = false;
            for(int i = 0; i < N; ++i) {
                const vector<int> &list = materials[i];
                if(list.size() == 0) continue;
                ULL acc = 0;
                for(vector<int>::const_iterator it = list.begin(); it != list.end(); ++it) {
                    acc += memo[*it];
                }
                if(acc < memo[i]) {
                    memo[i] = acc;
                    updated = true;
                }
            }
            if(!updated) break;
        }
        string target;
        cin >> target;
        cout << memo[dict.get(target)] << endl;
    }
    return 0;
}
