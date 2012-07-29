#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main() {
    while(true) {
        int N, M;
        cin >> N >> M;
        if(!N && !M) break;

        vector<vector<int> > v(N+1);
        vector<bool> invite(N+1, false);
        for(int i = 0; i < M; ++i) {
            int a, b;
            cin >> a >> b;
            v[a].push_back(b);
            v[b].push_back(a);
        }
        for(int i = 0; i < v[1].size(); ++i) {
            int person = v[1][i];
            invite[person] = true;
            for(int j = 0; j < v[person].size(); ++j) {
                invite[v[person][j]] = true;
            }
        }

        int cnt = 0;
        for(int i = 2; i < invite.size(); ++i) {
            if(invite[i]) ++cnt;
        }
        cout << cnt << endl;
    }
    return 0;
}
