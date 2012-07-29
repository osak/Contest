#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    while(true) {
        int N;
        cin >> N;
        if(!N) break;
        
        vector<vector<int> > v(N, vector<int>(N, 0));

        for(int i = 0; i < N; ++i) 
            for(int j = 0; j < N; ++j)
                cin >> v[i][j];

        vector<vector<int> > cnt(N, vector<int>(N, 0));

        for(int i = 0; i < N; ++i) {
            int minpos = 0;
            for(int j = 0; j < N; ++j) if(v[i][minpos] > v[i][j]) minpos = j;
            for(int j = 0; j < N; ++j) if(v[i][j] == v[i][minpos]) cnt[i][j]++;
        }
        
        for(int j = 0; j < N; ++j) {
            int maxpos = 0;
            for(int i = 0; i < N; ++i) if(v[maxpos][j] < v[i][j]) maxpos = i;
            for(int i = 0; i < N; ++i) if(v[i][j] == v[maxpos][j]) cnt[i][j]++;
        }

        int res = 0;
        for(int i = 0; i < N; ++i) 
            for(int j = 0; j < N; ++j) 
                if(cnt[i][j] == 2) res = v[i][j];

        cout << res << endl;
    }
    return 0;
}
