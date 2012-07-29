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
    if(seen[visited]) return false;
    seen[visited] = true;

    visited[cur]++;
    if(visited[cur] == 1) {
        int remain = 0;
        for(int i = cur+1; i < N; ++i) {
            if(graph[cur][i]) {
                visited[i]++;
            }
            else if(visited[i] == 0) {
                ++remain;
            }
        }
        ansset.push_back(cur);
        rec(cur+1, graph, visited, ansset, remain, cnt+1);
        ansset.pop_back();
        for(int i = cur+1; i < N; ++i) {
            if(graph[cur][i]) {
                visited[i]--;
            }
        }
    }
    rec(cur+1, graph, visited, ansset, remain_cnt-1, cnt);
    visited[cur]--;
    return true;
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

    vector<int> visited(N, 0);
    vector<int> ansset;
    rec(0, graph, visited, ansset, N, 0);

    for(vector<int>::iterator it = maxset.begin(); it != maxset.end(); ++it) {
        cout << (*it)+1 << ' ';
    }
    cout << endl;

    return 0;
}
