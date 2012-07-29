#include <iostream>
#include <vector>
#include <map>

using namespace std;

int maxans;
vector<int> maxset;
map<vector<int>, int> seen;

bool rec(int cur, const vector<vector<int> > &graph, vector<int> &visited, vector<int> &ansset, int remain_cnt, int cnt) {
    const int N = graph.size();
    if(cnt + remain_cnt <= maxans) return false;
    if(cnt > maxans) {
        maxans = cnt;
        maxset = ansset;
    }
    cout << maxans << ' ' << cnt << ' ' << cur << endl;
    visited[cur] = true;

    int remain = 0;
    for(int i = cur+1; i < N; ++i) {
        if(graph[cur][i]) {
            visited[i]++;
        }
        else if(visited[i] == 0) {
            ++remain;
        }
    }

    if(!seen[visited]) {
        seen[visited] = true;
        for(int i = cur+1; i < N; ++i) {
            if(visited[i]) continue;
            ansset.push_back(i);
            rec(i, graph, visited, ansset, remain+1, cnt+1);
            ansset.pop_back();
        }
    }

    for(int i = cur+1; i < N; ++i) {
        if(graph[cur][i]) {
            visited[i]--;
        }
    }
}

int main() {
    int N;
    cin >> N;

    vector<int> xs(N);
    for(int i = 0; i < N; ++i) {
        cin >> xs[i];
    }

    vector<vector<int> > graph(N, vector<int>(N, 0));
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            if(xs[i] % xs[j] == 0) {
                graph[i][j] = graph[j][i] = 1;
            }
        }
    }

    for(int i = 0; i < N; ++i) {
        vector<int> visited(N, 0);
        vector<int> ansset;
        ansset.push_back(i);
        for(int j = 0; j < i; ++j) visited[j] = true;
        rec(i, graph, visited, ansset, N-1, 1);
    }

    for(vector<int>::iterator it = maxset.begin(); it != maxset.end(); ++it) {
        cout << (*it)+1 << ' ';
    }
    cout << endl;

    return 0;
}
