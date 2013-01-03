#include <iostream>
#include <vector>
#include <cstdio>
#include <set>

using namespace std;

int N, M;
void big(int M) {
    while(M--) {
        int a, b;
        scanf("%d %d", &a, &b);
        puts("no");
    }
}

set<int> graph[500];
vector<int> used(500);
bool check(int pos, int prev) {
    used[pos] = 1;
    for(set<int>::const_iterator it = graph[pos].begin(); it != graph[pos].end(); ++it) {
        if(*it == prev) continue;
        if(*it != prev && used[*it]) return false;
        if(!check(*it, pos)) return false;
    }
    return true;
}

int main() {
    scanf("%d %d", &N, &M);
    if(N > 450) {
        big(M);
        return 0;
    }
    for(int i = 0; i < N; ++i) {
        for(int j = i+1; j < N; ++j) {
            graph[i].insert(j);
            graph[j].insert(i);
        }
    }
    int edges = N*(N-1)/2;
    while(M--) {
        int a, b;
        scanf("%d %d", &a, &b);
        --a; --b;
        if(graph[a].count(b)) { // erase
            graph[a].erase(b);
            graph[b].erase(a);
            --edges;
        } else { // put
            graph[a].insert(b);
            graph[b].insert(a);
            ++edges;
        }
        bool forest = false;
        if(edges <= N-1) {
            fill(used.begin(), used.end(), 0);
            forest = true;
            for(int i = 0; i < N; ++i) {
                if(!used[i]) {
                    if(!check(i, -1)) {
                        forest = false;
                        break;
                    }
                }
            }
        }
        puts(forest?"yes":"no");
    }
    return 0;
}
