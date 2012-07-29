#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Tag { 
    int s, c, j;
};

int main() {
    while(true) {
        int N, M;
        cin >> N >> M;
        if(!N && !M) break;

        vector<Tag> tags(N);
        vector<int> mincost(M, -1);
        for(int i = 0; i < N; ++i) cin >> tags[i].s >> tags[i].c >> tags[i].j;

        for(int i = 0; i < M; ++i) {
            int S, P;
            cin >> S >> P;
            for(int j = 0; j < N; ++j) {
                int cnt = ceil((double)P/tags[j].p);
                if(tags[j].s*cnt > S) continue;
                mincost[i] = min(mincost[i], tags[j].c*cnt);
            }
        }

        int ans = 10000*100*10;
        vector<int> v(M, 1);
        for(int i = 0; i < ceil(M/2); ++i) v[i] = 0;
        do {
            int sum = 0;
            for(int i = 0; i < M; ++i) if(v[i]==0) sum +=mincost[i];
            ans = min(ans, sum);
        } while(next_permutation(v.begin(). v.end()));

        cout << ans << endl;
    }
    return 0;
}
