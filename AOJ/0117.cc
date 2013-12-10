//Name: A reward for a Carpenter
//Level: 2
//Category: グラフ,Graph,最短経路
//Note:

/**
 * 始点から終点までの最短経路と、終点から始点までの最短経路をそれぞれ求めればよい。
 * 方法は色々あるが、ここでは頂点数が少ないためWarshall-Floydを用いた。
 *
 * オーダーはO(N^3)。
 */
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

bool solve() {
    int N, M;
    cin >> N >> M;
    vector<vector<int>> graph(N, vector<int>(N, 10000));
    for(int i = 0; i < M; ++i) {
        string s;
        cin >> s;
        for(char &c : s) {
            if(c == ',') c = ' ';
        }
        istringstream is(s);
        int a, b, c, d;
        is >> a >> b >> c >> d;
        graph[a-1][b-1] = c;
        graph[b-1][a-1] = d;
    }
    int S, T, A, B;
    {
        string s;
        cin >> s;
        for(char &c : s) {
            if(c == ',') c = ' ';
        }
        istringstream is(s);
        is >> S >> T >> A >> B;
        --S; --T;
    }
    for(int k = 0; k < N; ++k) {
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
            }
        }
    }
    cout << A-B-graph[S][T]-graph[T][S] << endl;
    return false;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
