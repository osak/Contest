//Name: Building Roads
//Level: 2
//Category: 最小全域木,Kruscal
//Note:

/*
 * Kruscal法で最小全域木を求めればよい．
 */
#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <complex>

using namespace std;

typedef complex<double> Point;

struct Tag {
    double length;
    int a, b;

    Tag(double l, int a, int b) : length(l), a(a), b(b) {}

    bool operator < (const Tag &other) const {
        return length < other.length;
    }
};

int root(int i, vector<int> &roots) {
    if(roots[i] == i) return i;
    return roots[i] = root(roots[i], roots);
}

void unite(int i, int j, vector<int> &roots, vector<int> &levels) {
    i = root(i, roots);
    j = root(j, roots);
    if(i == j) return;
    if(levels[i] < levels[j]) {
        roots[i] = j;
    } else {
        roots[j] = i;
        if(levels[i] == levels[j]) ++levels[i];
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int N, M;
    cin >> N >> M;
    vector<Point> v(N);
    vector<int> roots(N), levels(N, 0);
    for(int i = 0; i < N; ++i) {
        cin >> v[i].real() >> v[i].imag();
        roots[i] = i;
    }
    for(int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        unite(a, b, roots, levels);
    }
    vector<Tag> edges;
    for(int i = 0; i < N; ++i)
        for(int j = i+1; j < N; ++j)
            edges.push_back(Tag(abs(v[i]-v[j]), i, j));
    sort(edges.begin(), edges.end());
    double ans = 0;
    for(vector<Tag>::iterator it = edges.begin(); it != edges.end(); ++it) {
        if(root(it->a, roots) != root(it->b, roots)) {
            ans += it->length;
            unite(it->a, it->b, roots, levels);
        }
    }
    printf("%.2f\n", ans);
    return 0;
}
