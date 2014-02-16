//Name: ARCたんクッキー
//Level: 4
//Category: 数学,Math,GCD,最大公約数,SegmentTree
//Note:

/**
 * 問題を整理すると、数列に対して
 * ・[l, r]の範囲のGCD
 * ・[l, r]の範囲に均一に加算
 * のふたつのクエリを高速に処理できればよい。
 *
 * ここで、ユークリッドの互除法から明らかなように
 *   gcd(a+k, b+k) = gcd(a-b, b+k)
 * が成立する。
 * 同様にして、
 *   gcd(a+k, b+k, c+k) = gcd(a-b, b-c, c+k)
 * したがって、特定の区間に関して
 *   gcd(|v[a+1]-v[a]|, |v[a+2]-v[a+1]|, ...)
 * を事前に計算しておくことで、区間に値kを加えた時のGCDはO(1)で求められる。
 *
 * 以下では平方分割によってメンテナンスしている。
 * オーダーはO(MN√N)。
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define TIMES(i_, n_) for(int i_ = 0; i_ < (n_); ++(i_))

typedef long long LL;
const int BUCKET_SIZE = 317;

LL gcd(LL a, LL b) {
    if(a < b) swap(a, b);
    while(b) {
        const LL tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}

bool solve() {
    int N;
    if(!(cin >> N)) return false;
    if(!N) return false;

    const int BUCKETS = (N+BUCKET_SIZE-1) / BUCKET_SIZE;
    vector<LL> v(N, 0);
    vector<LL> bucket(BUCKETS, 0);
    vector<LL> bucket_add(BUCKETS, 0);
    vector<LL> base_gcd(BUCKETS, 0);
    for(LL &a : v) {
        cin >> a;
    }
    TIMES(i, BUCKETS) {
        const int left = i * BUCKET_SIZE;
        const int right = min(N, (i+1) * BUCKET_SIZE);
        if(left == right) break;

        bucket[i] = v[left];
        base_gcd[i] = 0;
        for(int j = left+1; j < right; ++j) {
            bucket[i] = gcd(bucket[i], v[j]);
            base_gcd[i] = gcd(base_gcd[i], abs(v[j] - v[j-1]));
        }
    }

    int M;
    cin >> M;
    while(M--) {
        int t, a, b;
        cin >> t >> a >> b;
        --a; --b;
        const int bucketA = a / BUCKET_SIZE;
        const int bucketB = b / BUCKET_SIZE;
        if(t == 0) {
            LL res = v[a] + bucket_add[bucketA];
            for(int i = a+1; i < min(b+1, min(N, (bucketA+1) * BUCKET_SIZE)); ++i) {
                res = gcd(res, v[i] + bucket_add[bucketA]);
            }
            for(int i = bucketA+1; i < bucketB; ++i) {
                res = gcd(res, bucket[i]);
            }
            if(bucketB != bucketA) {
                for(int i = BUCKET_SIZE*bucketB; i <= b; ++i) {
                    res = gcd(res, v[i] + bucket_add[bucketB]);
                }
            }
            cout << res << endl;
        } else {
            for(int i = bucketA*BUCKET_SIZE; i < min(N, (bucketA+1) * BUCKET_SIZE); ++i) {
                v[i] += bucket_add[bucketA];
                if(i >= a && i <= b) v[i] += t;
            }
            bucket_add[bucketA] = 0;
            base_gcd[bucketA] = 0;
            for(int i = bucketA*BUCKET_SIZE+1; i < min(N, (bucketA+1) * BUCKET_SIZE); ++i) {
                base_gcd[bucketA] = gcd(base_gcd[bucketA], abs(v[i]-v[i-1]));
            }
            bucket[bucketA] = gcd(v[a], base_gcd[bucketA]);

            for(int i = bucketA+1; i < bucketB; ++i) {
                bucket_add[i] += t;
                bucket[i] = gcd(base_gcd[i], v[i * BUCKET_SIZE] + bucket_add[i]);
            }

            if(bucketB != bucketA) {
                for(int i = BUCKET_SIZE*bucketB; i < min(N, BUCKET_SIZE*(bucketB+1)); ++i) {
                    v[i] += bucket_add[bucketB];
                    if(i <= b) v[i] += t;
                }
                bucket_add[bucketB] = 0;
                base_gcd[bucketB] = 0;
                for(int i = BUCKET_SIZE*bucketB+1; i < min(N, (bucketB+1)*BUCKET_SIZE); ++i) {
                    base_gcd[bucketB] = gcd(base_gcd[bucketB], abs(v[i]-v[i-1]));
                }
                bucket[bucketB] = gcd(v[b], base_gcd[bucketB]);
            }
        }
    }
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
