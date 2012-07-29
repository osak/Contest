#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <set>

#define FOREACH(v, E) for(__typeof(E.begin()) v = E.begin(); v != E.end(); ++v)

using namespace std;

typedef long long LL;

int main() {
    vector<int> is_prime(32000000, true);
    vector<int> primes;

    is_prime[0] = is_prime[1] = false;
    primes.push_back(2);
    for(int i = 3; i < is_prime.size(); i += 2) {
        if(is_prime[i]) {
            primes.push_back(i);
            if(i < (1<<16)) for(unsigned j = i*i; j < is_prime.size(); j += i) is_prime[j] = false;
        }
    }
    cout << primes.size() << endl;

    while(true) {
        LL N;
        cin >> N;
        if(!N) break;

        double ans = 1;
        queue<LL> q;
        set<LL> used;

        FOREACH(p, primes) {
            if(*p > N) break;
            q.push(*p);
        }
        while(!q.empty()) {
            LL orgn = q.front();
            cout << orgn << endl;
            q.pop();
            
            vector<pair<int, int> > v;
            double sn = 1;
            LL n = orgn;
            FOREACH(p, primes) {
                int cnt = 0;
                double s = 1;
                while(n % *p == 0) {
                    ++cnt;
                    n /= *p;
                    s += pow(*p, cnt);
                }
                sn *= s;
                v.push_back(make_pair(*p, cnt));
                if(n == 1) break;
            }
            if(n != 1) {
                sn *= 1+n;
                v.push_back(make_pair(n, 1));
            }
            ans = max(ans, sn/orgn);
            int lim = N / orgn;
            FOREACH(p, primes) {
                if(*p > lim) break;
                LL next = orgn * *p;
                if(used.count(next) > 0) continue;
                q.push(next);
                used.insert(next);
            }
        }
        printf("%.6f\n", ans);
    }
    return 0;
}
