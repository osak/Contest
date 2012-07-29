#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>

using namespace std;

struct Dict {
    map<string,int> dict;

    int get(const string &name) {
        if(dict.count(name) > 0) return dict[name];
        const int newnum = dict.size();
        return dict[name] = newnum;
    }
};

int getroot(int x, vector<int> &roots) {
    if(roots[x] == x) return x;
    return roots[x] = getroot(roots[x], roots);
}

void unite(int x, int y, vector<int> &roots) {
    const int a = getroot(x, roots);
    const int b = getroot(y, roots);
    if(a != b) {
        roots[a] = b;
    }
}

map<long long, int> memo;
int find_max_score(const vector<long long> &graph, vector<int> &roots, const vector<int> &scores, int pos, long long used) {
    const int N = graph.size();
    int score = 0;

    long long tmp = used;
    if(memo.count(tmp)) return memo[tmp];
    tmp |= 1LL<<pos;
    //const int M = graph[pos].size();
    /*
    for(int j = 0; j < M; ++j) {
        tmp |= 1LL << graph[pos][j];
    }
    */
    tmp |= graph[pos];

    for(int i = 0; i < N; ++i) {
        if(getroot(pos, roots) != getroot(i, roots)) continue;
        if(tmp & (1LL<<i)) continue;

        //cout << pos << ' ' << i << endl;
        score = max(score, find_max_score(graph, roots, scores, i, tmp));
    }

    return memo[tmp] = score + scores[pos];
}

int main() {
    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        memo.clear();
        vector<long long> neighbor(N, 0);
        vector<int> scores(N);
        vector<int> roots(N, 0);
        for(int i = 0; i < N; ++i) roots[i] = i;
        Dict dict;
        for(int i = 0; i < N; ++i) {
            string name;
            int score, n;
            cin >> name >> score >> n;
            int cid = dict.get(name);
            scores[cid] = score;
            while(n--) {
                string neighbor_name;
                cin >> neighbor_name;
                int nid = dict.get(neighbor_name);
                //neighbor[cid].push_back(nid);
                neighbor[cid] |= 1LL << nid;
                unite(cid, nid, roots);
            }
        }

        set<int> visited_graph;
        vector<int> max_score(N, 0);
        for(int i = 0; i < N; ++i) {
            if(i != 0 && roots[i] == roots[0]) continue;
            const int partial_score = find_max_score(neighbor, roots, scores, i, 0LL);
            //cout << i << ' ' << partial_score << endl;
            max_score[roots[i]] = max(max_score[roots[i]], partial_score);
        }
        
        int sum = 0;
        for(int i = 0; i < N; ++i) {
            sum += max_score[i];
        }
        cout << sum << endl;
    }

    return 0;
}
