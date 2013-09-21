#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

typedef long long LL;
const LL MOD = 1000000007LL;

LL gcd(LL a, LL b) {
    if(a < b) swap(a, b);
    while(b > 0) {
        LL tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}

LL lcm(LL a, LL b) {
    if(a == 0 || b == 0) return 0;
    return a / gcd(a, b) * b;
}

LL fastpow(LL a, LL x) {
    LL res = 1;
    LL ord = a % MOD;
    while(x) {
        if(x & 1) {
            res *= ord;
            res %= MOD;
        }
        ord *= ord;
        ord %= MOD;
        x >>= 1;
    }
    return res;
}

LL inv(LL a) {
    return fastpow(a, MOD-2);
}

LL buf[400000];
void update(int left, int right, int pos, int rl, int rr, LL val) {
    if(rr <= left || rl >= right) return;
    if(rl+1 == rr) {
        buf[pos] += val;
    } else {
        const int center = (rl+rr) / 2;
        update(left, right, pos*2, rl, center, val);
        update(left, right, pos*2+1, center, rr, val);
        buf[pos] = lcm(buf[pos*2], buf[pos*2+1]);
    }
}

LL query(int left, int right, int pos, int rl, int rr) {
    if(rr <= left || rl >= right) return 1;
    if(rl+1 == rr) return buf[pos];
    if(left <= rl && rr <= right) {
        return buf[pos];
    }
    const int center = (rl+rr) / 2;
    LL res = 1;
    res = lcm(res, query(left, right, pos*2, rl, center));
    res = lcm(res, query(left, right, pos*2+1, center, rr));
    return res;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int N, Q;
    scanf("%d %d", &N, &Q);
    vector<int> p(N);
    vector<LL> loop_sum(N, 0);
    vector<LL> invs(41);
    for(int i = 0; i < 41; ++i) {
        invs[i] = inv(i);
    }
    for(int i = 0; i < N; ++i) {
        int n;
        scanf("%d", &n);
        p[i] = n;
    }
    for(int i = 0; i < N; ++i) {
        int sum = 0;
        int len = 0;
        int cur = i+1;
        do {
            cur = p[cur-1];
            sum += cur;
            ++len;
        } while(cur != i+1);
        loop_sum[i] = (sum % MOD) * invs[len] % MOD;
        update(i, i+1, 1, 0, N, len);
        //cout << loop_len[i] << ' ' << loop_sum[i] << endl;
    }
    for(int i = 1; i < N; ++i) {
        loop_sum[i] += loop_sum[i-1];
        loop_sum[i] %= MOD;
    }
    while(Q--) {
        int l, r;
        scanf("%d %d", &l, &r);
        --l; --r;
        LL len = query(l, r+1, 1, 0, N) % MOD;
        LL per = loop_sum[r] - (l == 0 ? 0 : loop_sum[l-1]);
        per = (per + MOD) % MOD;
        LL ans = per * len % MOD;
        cout << ans << endl;
    }

    /*
    // test
    while(Q--) {
        int l, r;
        cin >> l >> r;
        --l; --r;
        LL whole_len = 1;
        for(int i = l; i <= r; ++i) {
            whole_len = lcm(whole_len, loop_len[i]);
        }
        LL sum = 0;
        for(int i = l; i <= r; ++i) {
            sum += loop_sum[i] * (whole_len / loop_len[i]);
            sum %= MOD;
        }
        cout << sum << endl;
    }
    */
    return 0;
}
