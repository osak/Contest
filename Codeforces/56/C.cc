#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <queue>
#include <cmath>

using namespace std;

typedef long long LL;

vector<int> primes;

LL gcd(LL a, LL b) {
    if(b > a) return gcd(b, a);
    while(b) {
        LL mod = a % b;
        a = b;
        b = mod;
    }
    return a;
}

void gen_primes(int n) {
    vector<int> bit(n+1, 1);
    primes.push_back(2);
    int lim = sqrt(n)+1;
    for(int i = 3; i <= n; i += 2) {
        if(bit[i]) {
            primes.push_back(i);
            if(i > lim) continue;
            for(int j = i*i; j <= n; j += i) bit[j] = 0;
        }
    }
}

void prime_division(LL n, vector<pair<LL,LL> > &facts) {
    for(int i = 0; i < primes.size(); ++i) {
        int cnt = 0;
        int p = primes[i];
        while(n % p == 0) {
            cnt++;
            n /= p;
        }
        if(cnt) facts.push_back(make_pair(p, cnt));
        if(n == 1) break;
    }
    if(n > 1) facts.push_back(make_pair(n, 1));
}

void divisors(const vector<pair<LL,LL> > &facts, vector<LL> &divs) {
    divs.push_back(1);
    for(int i = 0; i < facts.size(); ++i) {
        vector<LL> tmp;
        LL p = facts[i].first;
        LL acc = p;
        for(LL j = 1; j <= facts[i].second; ++j) {
            for(int k = 0; k < divs.size(); ++k) tmp.push_back(divs[k]*acc);
            acc *= p;
        }
        divs.insert(divs.end(), tmp.begin(), tmp.end());
    }
}

bool find_mus(const vector<vector<pair<LL,LL> > > &v, const set<int> &cn, vector<LL> &table) {
    int N = v.size();
    int start = *cn.begin();
    int to = 0;
    for(to = 0; to < N; ++to) if(v[start][to].first != 0) break;
    LL pr = v[start][to].first * v[start][to].second;

    if(cn.size() == 1) return true;

    vector<pair<LL,LL> > facts;
    vector<LL> divs;
    prime_division(pr, facts);
    divisors(facts, divs);
    for(vector<LL>::iterator it = divs.begin(); it != divs.end(); ++it) {
        queue<int> q;
        vector<int> used(N, 0);
        q.push(start);
        table[start] = *it;
        used[start] = 1;
        bool found = true;
        while(!q.empty()) {
            int n = q.front();
            q.pop();
            for(int i = 0; i < N; ++i) {
                if(v[n][i].first != 0) {
                    LL pr = v[n][i].first*v[n][i].second;
                    if(pr % table[n] != 0) {
                        found = false;
                        goto next;
                    }
                    if(used[i] && table[i] != pr/table[n]) {
                        found = false;
                        goto next;
                    }
                    table[i] = pr / table[n];
                    if(gcd(table[i], table[n]) != v[n][i].first) {
                        found = false;
                        goto next;
                    }
                    if(!used[i]) q.push(i);
                    used[i] = 1;
                }
            }
        }
next:
        if(found) return true;
    }
    return false;
}

int main() {
    int N, M;
    cin >> N >> M;
    vector<vector<pair<LL, LL> > > v(N, vector<pair<LL,LL> >(N, make_pair(0, 0)));

    gen_primes(1000000);
    for(int i = 0; i < M; ++i) {
        int a, b;
        pair<LL,LL> p;
        cin >> a >> b >> p.first >> p.second;
        --a; --b;
        v[a][b] = v[b][a] = p;
    }

    vector<set<int> > connections;
    vector<int> used(N, 0);
    while(true) {
        set<int> s;
        queue<int> q;
        int start = 0;
        for(start = 0; start < N; ++start) if(!used[start]) break;
        if(start == N) break;
        q.push(start);
        used[start] = 1;
        while(!q.empty()) {
            int n = q.front();
            q.pop();
            s.insert(n);
            for(int i = 0; i < N; ++i) {
                if(!used[i] && v[n][i].first != 0) {
                    q.push(i);
                    used[i] = 1;
                }
            }
        }
        connections.push_back(s);
    }

    vector<LL> table(N, 1);
    bool found = true;
    for(int i = 0; i < connections.size(); ++i) {
        if(!find_mus(v, connections[i], table)) {
            found = false;
            break;
        }
    }
    if(found) {
        cout << "YES" << endl;
        for(int i = 0; i < N; ++i) cout << table[i] << " ";
        cout << endl;
    }
    else cout << "NO" << endl;

    return 0;
}
