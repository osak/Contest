#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N, M, K;
    cin >> N >> M >> K;

    vector<vector<int> > vs(M+1);
    for(int i = 0; i < N; ++i) {
        int v;
        cin >> v;
        vs[v].push_back(i);
    }

    int ans = 1;
    for(int i = 0; i < M+1; ++i) {
        vector<int> &vv = vs[i];
        if(vv.size() == 0) continue;
        vv.push_back(N+(K+1)*2);

        int left = 0, right = 0;
        int delcnt = 0;
        while(right+1 < vv.size()) {
            int nr = right+1;
            delcnt += vv[nr]-vv[right]-1;
            right = nr;

            while(delcnt > K) {
                int nl = left+1;
                int dc = vv[nl]-vv[left]-1;
                delcnt -= dc;
                left = nl;
            }
            ans = max(ans, right-left+1);
        }
    }

    cout << ans << endl;

    return 0;
}
