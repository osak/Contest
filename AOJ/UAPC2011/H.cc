#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    while(true)  {
        int N;
        cin >> N;
        if(!N) break;

        int blen = N*(N+1)/2;
        vector<long long> v(blen);
        for(int i = 0; i < blen; ++i) cin >> v[i];

        long long lim = v.back() / 3;
        vector<int> ans;
        for(int i = 3; i < lim; i += 2) {
            if(v.back() % i != 0) continue;

            bool ok = true;
            vector<int> as(N+1);
            as[N] = i;
            for(int j = N-1; j >= 0 ; --j) {
                int idx = (N+(N-j+1))*(j) / 2;
                if(v[idx] % as[j+1] != 0) {
                    ok = false;
                    break;
                }
                as[j] = v[idx] / as[j+1];
            }
            if(ok) {
                ans = as;
                break;
            }
        }
        cout << ans[0] << endl;
        sort(ans.begin()+1, ans.end());
        for(int i = 1; i < N+1; ++i) cout << ans[i] << ' ';
        cout << endl;
    }
    return 0;
}
