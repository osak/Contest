//Name: Can I go there?
//Level: 4
//Category: グラフ,Graph,行列累乗,繰り返し二乗法
//Note:

/**
 * 直前にいた頂点に戻るような移動ができないので、頂点を(現在の頂点,直前にいた頂点)のペアに拡張して
 * グラフを作り直す。
 * こうすると、このグラフ上で長さがちょうどZの経路があるか判定する問題になるため、隣接行列の累乗をすればよい。
 *
 * オーダーはO(M^3 log Z)。
 */
#include <iostream>
#include <vector>

using namespace std;

void matmul(vector<vector<bool>> &a, const vector<vector<bool>> &b) {
    const int N = a.size();
    vector<vector<bool>> res(N, vector<bool>(N, false));

    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            for(int k = 0; k < N; ++k) {
                res[i][j] = res[i][j] || (a[i][k] && b[k][j]);
            }
        }
    }
    a.swap(res);
}

bool solve() {
    int N, M, Z;
    cin >> N >> M >> Z;
    if(!N && !M && !Z) return false;

    vector<pair<int,int>> nodes; // (node, prev)
    for(int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        nodes.push_back(make_pair(a, b));
        nodes.push_back(make_pair(b, a));
    }
    nodes.push_back(make_pair(0, -1));
    const int K = nodes.size();
    vector<vector<bool>> mat(K, vector<bool>(K, false));
    for(int i = 0; i < K; ++i) {
        for(int j = 0; j < K; ++j) {
            if(nodes[i].first == nodes[j].second && nodes[j].first != nodes[i].second) mat[i][j] = true;
        }
    }
    vector<vector<bool>> res(K, vector<bool>(K, false));
    for(int i = 0; i < K; ++i) {
        res[i][i] = true;
    }
    while(Z) {
        if(Z % 2 == 1) {
            matmul(res, mat);
        }
        matmul(mat, mat);
        Z /= 2;
    }
    for(int i = 0; i < K; ++i) {
        for(int j = 0; j < K; ++j) {
            if(nodes[i].first == 0 && nodes[j].first == N-1 && res[i][j]) {
                cout << "yes" << endl;
                return true;
            }
        }
    }
    cout << "no" << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
