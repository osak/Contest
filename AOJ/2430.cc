//Name: Longest Increasing Sequence
//Level: 4
//Category: DP,最長増加列
//Note:

/*
 * dp[a][b] = 区間[a,b)を一つにまとめたとき，[0,b)における最長増加列長
 * としてDPする．
 * dp[a][b] = (max_(0 ≦ k < a && sumof[k,a) < sumof[a,b) ) dp[k][a]) + 1 であることは容易に分かるが，まともに計算するとO(N^3)になって解けない．
 * ここで sumof[a,b) > sumof[a,c) であるとき，dp[a][b]においてmaxを与えるkはdp[a][c]においてmaxを与えるk'と同じであるか，sumof[k,a) > sumof[k',a)を満たすかであることを考える．
 * するとあるaについて ∀0≦k<a sumof[k,a) と ∀a<l≦N sumof[a,l) を全て求めてこの順にソートし，sumが小さいほうから見ていくと良いことが分かる．
 * このとき左側の区間がきたらdpの最適解(上のmax)を更新し，右側の区間がきたらそのときのmaxを利用して配るDPでDP表を更新する．
 */
#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int N;
    cin >> N;
    // for sum of [a, b), just calc sum[a]-sum[b]
    vector<long long> as(N);
    vector<long long> sum(N+1, 0);
    for(int i = 0; i < N; ++i) {
        cin >> as[i];
    }
    for(int i = N-1; i >= 0; --i) {
        sum[i] = sum[i+1] + as[i];
    }

    // dp[始点][終点] = [始点, 終点)を一つにしたとき，[0,終点)での最長増加列長
    vector<vector<int> > dp(N+1, vector<int>(N+1, numeric_limits<int>::min())), prev(N+1, vector<int>(N+1, numeric_limits<int>::min()));
    for(int right = 1; right <= N; ++right) {
        dp[0][right] = 1;
    }
    for(int cur = 1; cur < N; ++cur) {
        // 点curから始まる系列[cur, next)を考える．
        vector<pair<long long,int> > nums;
        // 点curから始まる系列を与え得る直前の状態を列挙する．
        for(int prev_i = 0; prev_i < cur; ++prev_i) {
            nums.push_back(make_pair(sum[prev_i] - sum[cur], -prev_i));
        }
        // 点curから始まる系列が到達し得る状態を列挙する．
        for(int right = cur+1; right <= N; ++right) {
            nums.push_back(make_pair(sum[cur] - sum[right], -right));
        }
        sort(nums.begin(), nums.end());
        int best = numeric_limits<int>::min();
        int best_prev = -1;
        for(vector<pair<long long,int> >::iterator it = nums.begin(); it != nums.end(); ++it) {
            int pos = -it->second;
            if(pos < cur) {
                if(best < dp[pos][cur]) {
                    // これより先，[pos,cur)から接続するのが最も効率が良い．
                    best = dp[pos][cur];
                    best_prev = pos;
                }
            } else if(pos > cur) {
                if(dp[cur][pos] < best+1) {
                    dp[cur][pos] = best+1;
                    prev[cur][pos] = best_prev;
                    //cout << cur << ' ' << pos << ' ' << dp[cur][pos] << endl;
                }
            }
        }
    }
    {
        // Nを終点とするDP表から最良の始点を選ぶ．
        int cur = -1;
        int best = 0;
        for(int left = 0; left < N; ++left) {
            if(dp[left][N] > best) {
                best = dp[left][N];
                cur = left;
            }
        }
        // 経路復元
        vector<int> checkpoint;
        int prev_cur = N;
        while(cur > 0) {
            checkpoint.push_back(cur);
            int next = prev[cur][prev_cur];
            prev_cur = cur;
            cur = next;
        }
        sort(checkpoint.begin(), checkpoint.end());
        cout << checkpoint.size()+1 << endl;
        for(vector<int>::iterator it = checkpoint.begin(); it != checkpoint.end(); ++it) {
            if(it != checkpoint.begin()) cout << ' ';
            cout << *it;
        }
        cout << endl;
    }
    return 0;
}
