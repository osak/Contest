#include <cstdio>
#include <ext/hash_map>
#include <cstring>
#include <vector>

using namespace std;
using namespace __gnu_cxx;

struct Tag {
    int n, m, f, prev, limited;

    Tag() {}
    Tag(int n, int m, int f, int p, int l) 
        : n(n), m(m), f(f), prev(p), limited(l) {}

    size_t operator ()(const Tag &t) const {
        return t.n*50
            +  t.m*50*50
            +  t.f*50*50*50
            +  t.prev*50*50*50*50
            +  t.limited*50*50*50*50*50;
    }

    bool operator ==(const Tag &other) const {
        return n == other.n
            && m == other.m
            && f == other.f
            && prev == other.prev
            && limited == other.limited;
    }
};

inline bool lucky(int d) {
    return d == 4 || d == 7;
}

inline int un_f(int f) {
    if(f < 0) return 0;
    return f;
}

int N;
vector<int> limit, c;
hash_map<Tag,long long,Tag> memo;
long long solve(int n, int m, int f, int prev, bool limited) {
    if(n == N) return 1;
    if(m == -1) {
        if(n > 0 && (((f==prev)!=0) != c[n-1])) return 0;
        return solve(n+1, (int)limit.size()-1, -1, f, true);
    }

    const Tag key(n, m, f, prev, limited);
    if(memo.count(key)) return memo[key];

    long long res = 0;
    int lim = limited ? limit[m] : 9;
    int bot = (m==0 && f==-1) ? 1 : 0;
    for(int d = bot; d <= lim; ++d) {
        int nf = lucky(d) ? un_f(f)+1 : (f==-1 && d==0) ? -1 : un_f(f);
        bool nl = limited && (d==lim);
        res += solve(n, m-1, nf, prev, nl);
        if(res > 2000000000LL) break;
    }
    printf("%lld\n", res);
    return memo[key] = res;
}

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        int M, K;
        scanf("%d %d %d", &N, &M, &K);
        c.clear();
        for(int i = 0; i < N-1; ++i) {
            int v;
            scanf("%d", &v);
            c.push_back(v==1);
        }
        limit.clear();
        {
            int tmp = M;
            while(tmp) {
                limit.push_back(tmp%10);
                tmp /= 10;
            }
        }
        memo.clear();

        vector<int> ans;
        int prevf = 0;
        long long acc = 0;
        for(int i = 0; i < N; ++i) {
            int num = 0;
            bool limited = true;
            int f = -1;
            for(int dpos = (int)limit.size()-1; dpos >= 0; --dpos) {
                int lim = limited ? limit[dpos] : 9;
                int bot = (dpos==0 && f==-1) ? 1 : 0;
                int digit = -1;
                for(int d = bot; d <= lim; ++d) {
                    int nf = lucky(d) ? un_f(f)+1 : (f==-1 && d==0) ? -1 : un_f(f);
                    bool nl = limited && (d==lim);
                    long long tmp = solve(i, dpos-1, nf, prevf, nl);
                    if(acc+tmp >= K) {
                        digit = d;
                        f = nf;
                        break;
                    }
                    acc += tmp;
                }
                if(digit == -1) {
                    ans.clear();
                    ans.push_back(-1);
                    goto end;
                }

                num *= 10;
                num += digit;
                limited = limited && (digit==lim);
            }
            ans.push_back(num);
            prevf = f;
        }

end:
        bool first = true;
        for(vector<int>::iterator it = ans.begin(); it != ans.end(); ++it) {
            if(!first) printf(" ");
            printf("%d", *it);
            first = false;
        }
        puts("");
    }

    return 0;
}
