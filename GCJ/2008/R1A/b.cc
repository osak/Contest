#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>

using namespace std;


int main() {
    int cases;
    cin >> cases;
    for(int C = 1; C <= cases; ++C) {
        int N, M;
        cin >> N >> M;

        vector<vector<int> > links(N+1);
        vector<int> favor_count(M);
        vector<int> favor_malted(M);
        vector<int> answer(N+1);

        fill(favor_malted.begin(), favor_malted.end(), -1);
        fill(answer.begin(), answer.end(), 0);
        for(int i = 0; i < M; ++i) {
            int T;
            cin >> T;
            favor_count[i] = T;
            while(T--) {
                int X, Y;
                cin >> X >> Y;
                if(Y == 0) links[X].push_back(i);
                else favor_malted[i] = X;
            }
        }
        int state = 0;
        while(true) {
            state = 0;
            for(int i = 0; i < M; ++i) {
                if(favor_count[i] == 0) {
                    state = -1;
                    goto endloop;
                }
                if(favor_count[i] == 1 && favor_malted[i] != -1) {
                    int flavor = favor_malted[i];
                    if(answer[flavor] == 1) continue;
                    answer[flavor] = 1;
                    favor_count[i] = INT_MAX;
                    for(int j = 0; j < links[flavor].size(); ++j) {
                        favor_count[links[flavor][j]]--;
                    }
                    state = 1;
                }
            }
            if(state == 0) break;
        }
endloop:
        cout << "Case #" << C << ": ";
        if(state == 0) {
            for(int i = 1; i <= N; ++i) {
                cout << answer[i] << " ";
            }
            cout << endl;
        }
        else {
            cout << "IMPOSSIBLE" << endl;
        }
    }
    return 0;
}
