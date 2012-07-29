#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;


struct poly
{
    int coeff[60];
    poly() { fill_n(coeff, 60, 0); }
    poly& operator+=(const poly& p)
    {
        for (int i = 0; i <= 50; i++) {
            coeff[i] += p.coeff[i];
        }
        return *this;
    }
    poly& operator-=(const poly& p)
    {
        for (int i = 0; i <= 50; i++) {
            coeff[i] -= p.coeff[i];
        }
        return *this;
    }
    bool operator<(const poly& p) const
    {
        for (int i = 50; i >= 0; i--) {
            if (coeff[i] != p.coeff[i]) {
                return coeff[i] < p.coeff[i];
            }
        }
        return false;
    }
};
poly operator-(poly p, const poly& q) { p -= q; return p; }
ostream& operator<<(ostream& os, const poly& p)
{
    bool first = true;
    for (int i = 50; i >= 0; i--) {
        if (p.coeff[i] > 0) {
            if (!first) {
                os << '+';
            }
            first = false;
            if (i == 0 || p.coeff[i] != 1) {
                os << p.coeff[i];
            }
            if (i != 0) {
                os << 'x';
                if (i != 1) {
                    os << '^' << i;
                }
            }
        } else if (i == 0 && first) {
            os << 0;
        }
    }
    return os;
}

poly edmonds_karp(const vector<vector<pair<int,poly> > >& g, int source, int sink)
{
    const int N = g.size();
    vector<vector<poly> > capacity(N, vector<poly>(N)), flow(N, vector<poly>(N));
    for (int v = 0; v < N; v++) {
        for (vector<pair<int,poly> >::const_iterator it = g[v].begin(); it != g[v].end(); ++it) {
            capacity[v][it->first] = it->second;
        }
    }
    poly max_flow;

    while (true) {
        vector<int> parent(N, -1);
        queue<int> q;
        q.push(source);
        while (!q.empty() && parent[sink] < 0) {
            const int v = q.front();
            q.pop();
            for (vector<pair<int,poly> >::const_iterator it = g[v].begin(); it != g[v].end(); ++it) {
                const int u = it->first;
                const poly& c = it->second;
                if (parent[u] < 0 && flow[v][u] < c) {
                    parent[u] = v;
                    if (u == sink) {
                        break;
                    }
                    q.push(u);
                }
            }
        }
        if (parent[sink] < 0) {
            break;
        }

        int u = parent[sink];
        poly aug = capacity[u][sink] - flow[u][sink];
        for (int v = sink; v != source; v = parent[v]) {
            u = parent[v];
            aug = min(aug, capacity[u][v] - flow[u][v]);
        }
        max_flow += aug;
        for (int v = sink; v != source; v = parent[v]) {
            u = parent[v];
            flow[u][v] += aug;
            flow[v][u] -= aug;
        }
    }
    return max_flow;
}

typedef string::const_iterator Iterator;
int number(Iterator& it, const Iterator& last)
{
    if (it == last || !isdigit(*it)) {
        return 1;
    }
    int n = 0;
    while (it != last && isdigit(*it)) {
        n = 10*n + *it-'0';
        ++it;
    }
    return n;
}

pair<int,int> term(Iterator& it, const Iterator& last)
{
    const int n = number(it, last);
    if (it == last) {
        return make_pair(0, n);
    }
    if (*it != 'x') {
        throw "x expected";
    }
    ++it;
    if (it != last && *it == '^') {
        ++it;
        const int e = number(it, last);
        return make_pair(e, n);
    } else {
        return make_pair(1, n);
    }
}

poly expr(Iterator& it, const Iterator& last)
{
    poly p;
    pair<int,int> r = term(it, last);
    p.coeff[r.first] = r.second;
    while (it != last && *it == '+') {
        ++it;
        r = term(it, last);
        p.coeff[r.first] = r.second;
    }
    return p;
}

poly parse(const string& s)
{
    Iterator it = s.begin(), last = s.end();
    return expr(it, last);
}

int main()
{
    int N, M;
    while (cin >> N >> M && N != 0) {
        vector<vector<pair<int,poly> > > g(N);
        for (int i = 0; i < M; i++) {
            int u, v;
            string s;
            cin >> u >> v >> s;
            --u;    --v;
            const poly p = parse(s);
            g[u].push_back(make_pair(v, p));
            g[v].push_back(make_pair(u, p));
        }
        cout << edmonds_karp(g, 0, N-1) << endl;
    }
    return 0;
}
