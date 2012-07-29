#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstdio>

using namespace std;

int calc_score(const vector<int> &ord, const vector<vector<int> > &graph, const vector<pair<int,int> > &to_see) {
    int score = 0;
    for(vector<pair<int,int> >::const_iterator it = to_see.begin(); it != to_see.end(); ++it) {
        if(graph[ord[it->first]][ord[it->second]]) ++score;
    }
    return score;
}

int main() {
    int T;
    scanf("%d", &T);
    srand(time(NULL));
    while(T--) {
        int N;
        scanf("%d", &N);
        vector<vector<int> > target(N, vector<int>(N));
        vector<vector<int> > graph(N, vector<int>(N));
        vector<pair<int,int> > to_see;
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                int v;
                scanf("%d", &v);
                target[i][j] = v;
                if(v) to_see.push_back(make_pair(i, j));
            }
        }
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                int v;
                scanf("%d", &v);
                graph[i][j] = v;
            }
        }

        vector<int> nodes(N), ans;
        int bestscore = 0;
        for(int i = 0; i < N; ++i) {
            nodes[i] = i;
        }

        vector<int> cur = nodes;
        int curscore = 0;

        random_shuffle(cur.begin(), cur.end());
        ans = cur;
        bestscore = curscore = calc_score(cur, graph, to_see);
        for(int CNT = 0; CNT < 2000; ++CNT) {
            vector<int> next_cand = cur;
            int next_best = curscore;

            for(int CN = 0; CN < 10; ++CN) {
                int a = rand() % N, b = rand() % N;
                vector<int> next = cur;
                swap(next[a], next[b]);

                int nc = calc_score(next, graph, to_see);
                if(nc > next_best) {
                    next_cand = next;
                    next_best = nc;
                }
            }
            if(next_cand == cur) {
                random_shuffle(cur.begin(), cur.end());
                next_best = calc_score(cur, graph, to_see);
            }
            cur = next_cand;
            curscore = next_best;
            if(curscore > bestscore) {
                ans = cur;
                bestscore = curscore;
            }
        }

        bool first = true;
        for(int i = 0; i < N; ++i) {
            if(!first) printf(" ");
            printf("%d", i+1);
            first = false;
        }
        puts("");
        first = true;
        for(int i = 0; i < N; ++i) {
            if(!first) printf(" ");
            printf("%d", ans[i]+1);
            first = false;
        }
        puts("");
        //printf("%d\n", bestscore);
    }

    return 0;
}
