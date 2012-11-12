//Name: Find the Multiples
//Level: 3
//Category: 素数,数論
//Note:

/*
 * Q≠2 かつ Q≠5 であれば，ある値がQの倍数のときは末尾の0を取り除いても(=10^kで割っても)Qの倍数のままである．
 * したがって下の位から重み1, 10%Q, 100%Q, ... , 10^(n-1)%Q を割り当てて累積和を取っておくと，
 * 桁iを最上位とするQの倍数の個数は j > i かつ sum[i]-sum[j] = 0 となる j の個数に等しい．
 * (これはつまり {a_i a_(i+1) a_(i+2) ... a_(j-1)} × 10^(N-j) が Q の倍数かどうか判定している)
 * これは累積和を下の桁から取りつつ，途中でそのような j の個数を覚えておいて足していけばよい．
 *
 * Q=2 または Q=5 のときは，値を10で割ると Q の倍数かどうかに影響を及ぼす．
 * 幸いにもこれらは末尾1桁だけで倍数判定が可能なので，上位の桁から見て行って
 * これらの倍数が出現したらそれより上位の非ゼロの桁の数を足していけばよい．
 *
 * オーダーはハッシュテーブルを用いて O(N)．
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <tr1/unordered_map>

using namespace std;

void init(int N, int S, int W, vector<int> &as) {
    int g = S;
    for(int i = 0; i < N; ++i) {
        as[i] = (g/7) % 10;
        if(g%2 == 0) g = g/2;
        else g = (g/2) ^ W;
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    while(true) {
        int N, S, W, Q;
        cin >> N >> S >> W >> Q;
        if(!N && !S && !W && !Q) break;
        vector<int> as(N);
        init(N, S, W, as);
        long long ans = 0;
        if(Q == 2) {
            int nonzero = 0;
            for(int i = 0; i < N; ++i) {
                if(as[i] != 0) ++nonzero;
                if(as[i] % 2 == 0) ans += nonzero;
            }
        } else if(Q == 5) {
            int nonzero = 0;
            for(int i = 0; i < N; ++i) {
                if(as[i] != 0) ++nonzero;
                if(as[i] % 5 == 0) ans += nonzero;
            }
        } else {
            vector<long long> sum(N, 0);
            tr1::unordered_map<long long,int> sumcnt;
            sumcnt[0] = 1;
            long long ord = 1;
            for(int i = N-1; i >= 0; --i) {
                if(i == N-1) sum[i] = as[i] % Q;
                else sum[i] = (sum[i+1] + static_cast<long long>(as[i])*ord) % Q;
                if(as[i] != 0) {
                    //cout << as[i] << ' ' << sumcnt[sum[i]] << endl;
                    ans += sumcnt[sum[i]];
                }
                sumcnt[sum[i]]++;
                ord *= 10;
                ord %= Q;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
