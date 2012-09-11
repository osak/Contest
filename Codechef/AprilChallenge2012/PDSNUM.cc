#include <cstdio>
#include <vector>
#include <ext/hash_map>
#include <cstring>

using namespace std;
using namespace __gnu_cxx;

/////////////////// メモ化用 //////////////////////
struct Tag {
    int n, rem, prod;

    Tag() {}
    Tag(int n, int r, int p) : n(n), rem(r), prod(p) {}

    bool operator ==(const Tag &other) const {
        return n == other.n && rem == other.rem && prod == other.prod;
    }

    size_t operator ()(const Tag &t) const {
        return t.prod + t.n + t.rem*10;
    }
};

struct Tag2 {
    int nth, d, sum, prod;

    Tag2() {}
    Tag2(int n, int d, int s, int p) : nth(n), d(d), sum(s), prod(p) {}

    bool operator ==(const Tag2 &other) const {
        return nth == other.nth && d == other.d && sum == other.sum && prod == other.prod; 
    }

    size_t operator ()(const Tag2&t) const {
        return t.prod + t.nth*10+t.d*100+t.sum*1000;
    }
};
/////////////////////////////////////////////////////

// n桁で総和がremになる数の個数を返す．
// 先頭が0になるものも含める．
// （rec(4, 4)で0022も数える等）
int memo[10][91];
int rec(int n, int rem) {
    if(rem == 0) return 1;
    if(n == 0) return 0;

    if(memo[n][rem] == -1) {
        int res = 0;
        for(int d = 0; d <= 9; ++d) {
            if(d > rem) break;
            res += rec(n-1, rem-d);
        }
        memo[n][rem] = res;
    }
    return memo[n][rem];
}

// 総和がsumになるn桁の数で，PDS Numberであるものを探索する．
// ただし，これより前の数で積prodが得られているものとする．
vector<hash_map<Tag,int,Tag> > memo2(91);
int rec2(int n, int rem, int prod, int sum) {
    if(n == 0) {
        if(rem == 0 && prod % sum == 0) return 1;
        return 0;
    }
    if(rem == 0) return 1;
    if(n*9 < rem) return 0;

    // 途中でprodがsumで割り切れるようになったら，その後はどう並んでも良い．
    if(prod >= 0 && prod % sum == 0) {
        return rec(n, rem);
    }

    const Tag key(n, rem, prod);
    if(memo2[sum].count(key)) return memo2[sum][key];

    int res = 0;
    for(int d = 0; d <= 9; ++d) {
        if(d > rem) break;
        int nprod = prod<0 ? d==0 ? -1 : d : prod*d;
        res += rec2(n-1, rem-d, nprod, sum);
    }
    return memo2[sum][key] = res;
}

hash_map<Tag2,int,Tag2> memo3;
int solve(int n) {
    int ans = 0;
    int prod = -1; // 「先頭からずっと0」は「積が0」と区別しないといけない
    int sum = 0;
    int pat = 0;

    // 上の桁から固定して，パターン数を数えていく．
    // 10^9番目のPDS Numberは10^9オーダで存在するっぽい
    for(int nth = 10; nth >= 1; --nth) {
        ans *= 10;
        int digit = -1;
        for(int d = 0; d <= 9; ++d) {
            int nprod = prod<0 ? d==0 ? -1 : d : prod*d;
            const Tag2 key(nth, d, sum, nprod);
            int subpat = 0;
            if(memo3.count(key) == 0) {
                for(int allsum = 1; allsum <= 90; ++allsum) {
                    if(allsum >= sum+d) subpat += rec2(nth-1, allsum-sum-d, nprod, allsum);
                }
                memo3[key] = subpat;
            }
            else {
                subpat = memo3[key];
            }

            //printf("%d\n", subpat);
            if(pat + subpat >= n) {
                digit = d;
                break;
            }
            pat += subpat;
        }
        if(digit == -1) {
            puts("NEVER REACH HERE!");
        }
        ans += digit;
        sum += digit;
        //printf("%dth digit: %d\n", nth, digit);
        if(ans != 0) {
            if(prod < 0) prod = 1;
            prod *= digit;
        }
    }
    return ans;
}

int main() {
    memset(memo, -1, sizeof(memo));
    while(true) {
        int N;
        scanf("%d", &N);
        if(!N) break;

        printf("%d\n", solve(N));
    }
    return 0;
}
