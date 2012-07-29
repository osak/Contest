#include <iostream>
#include <vector>
#include <climits>
#include <queue>

using namespace std;

int require_n_for_delta[601];
int visited[10001];

int get_n_for_delta(int d) {
    return require_n_for_delta[d+300];
}

int set_n_for_delta(int d, int n) {
    require_n_for_delta[d+300] = n;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    for(int i = 0; i < 601; ++i) {
        require_n_for_delta[i] = INT_MAX;
    }
    for(int i = 0; i < 10001; ++i) {
        visited[i] = -1;
    }

    int M, N;
    cin >> M >> N;
    for(int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;

        int d = b-a;
        if(get_n_for_delta(d) > a) {
            set_n_for_delta(d, a);
        }
    }

    queue<int> q;
    q.push(1);
    visited[1] = 1;
    while(!q.empty()) {
        int cur = q.front();
        q.pop();

        for(int delta = -300; delta <= 300; ++delta) {
            int next = cur + delta;
            if(next >= 0) {
                int n = get_n_for_delta(delta);
                if(cur >= n) {
                    if(visited[next] == -1) {
                        q.push(next);
                        visited[next] = visited[cur]+1;
                    }
                }
            }
        }
    }

    cout << visited[N] << endl;
    return 0;
}
