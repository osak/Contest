#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

int main() {
    int N, M, H, T;
    while(scanf("%d %d %d %d", &N, &M, &H, &T) != EOF) {
        vector<vector<int> > graph(N);
        for(int i = 0; i < M; ++i) {
            int a, b;
            scanf("%d %d", &a, &b);
            graph[a].push_back(b);
            graph[b].push_back(a);
        }
