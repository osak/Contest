//Name: The Enemy of My Enemy is My Friend
//Level: 4
//Category: 探索
//Note:

/*
 * 前から順番に選んでいく全探索に，
 * ・これより後に影響しない(隣り合っているものがない)ノードは必ず使う
 * ・これより後のノードを全て使っても最高スコアに届かないときはすぐに諦める
 * の枝刈りを入れている．
 */
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

typedef long long LL;

struct Dict {
    map<string,int> dict;

    int get(const string &str) {
        if(dict.count(str)) return dict[str];
        int id = dict.size();
        return dict[str] = id;
    }
};

int best = 0;
void dfs(int pos, LL used, int score, const vector<LL> &neighbors, const vector<LL> &neighbors_rem, const vector<int> &scores, const vector<int> &scores_rem) {
    const int N = neighbors.size();
    if(pos == N) {
        best = max(best, score);
        return; 
    }
    if(score + scores_rem[pos] <= best) {
        return;
    }
    LL mask = 1LL<<pos;

    if(!(used & mask)) {
        dfs(pos+1, used | neighbors[pos] | mask, score + scores[pos], neighbors, neighbors_rem, scores, scores_rem);
    }
    if((used & mask) || (pos+1 < N && (neighbors_rem[pos+1] & mask))) {
        dfs(pos+1, used, score, neighbors, neighbors_rem, scores, scores_rem);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        vector<LL> neighbors(N, 0);
        vector<int> scores(N, 0);
        Dict dict;
        for(int i = 0; i < N; ++i) {
            string name;
            int score, ncnt;
            cin >> name >> score >> ncnt;
            const int cid = dict.get(name);
            scores[cid] = score;
            while(ncnt--) {
                string nname;
                cin >> nname;
                const int nid = dict.get(nname);
                neighbors[cid] |= 1LL<<nid;
            }
        }

        vector<LL> neighbors_rem(N, 0);
        vector<int> scores_rem(N, 0);
        neighbors_rem[N-1] = neighbors[N-1];
        scores_rem[N-1] = scores[N-1];
        for(int i = N-2; i >= 0; --i) {
            neighbors_rem[i] = neighbors_rem[i+1] | neighbors[i];
            scores_rem[i] = scores_rem[i+1] + scores[i];
        }
        best = 0;
        dfs(1, neighbors[0] | 1, scores[0], neighbors, neighbors_rem, scores, scores_rem);
        cout << best << endl;
    }

    return 0;
}
