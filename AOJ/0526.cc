#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

int main() {
    while(true) {
        int N, K;
        cin >> N >> K;
        if(!N && !K) break;

        vector<vector<int> > v(N, vector<int>(N, -1));
        while(K--) {
            int cmd;
            cin >> cmd;
            if(cmd == 0) {
                int a, b;
                cin >> a >> b;
                --a; --b;
                cout << v[a][b] << endl;
            }
            else {
                int c, d, e;
                cin >> c >> d >> e;
                --c; --d;
                if(v[c][d] == -1 || e < v[c][d]) {
                    v[c][d] = v[d][c] = e;
                    for(int k = 0; k < 2; ++k) {
                        int mid = k ? c : d;
                        for(int i = 0; i < N; ++i) {
                            for(int j = 0; j < N; ++j) {
                                if(v[i][mid] != -1 && v[mid][j] != -1) {
                                    if(v[i][j] == -1) v[i][j] = v[i][mid]+v[mid][j];
                                    else v[i][j] = min(v[i][j], v[i][mid]+v[mid][j]);
                                    v[j][i] = v[i][j];
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}
