//Name: Learning Languages
//Level: 2
//Category: グラフ,探索
//Note:

/*
 * 人と言語それぞれに対応するノードを用意し，全ての人を連結にするために追加しなければならない辺数の最小値を求める．
 * これは基本的には初期状態における連結成分の数-1と等しい(どれかの連結成分に全て統合すればよい)．
 * ただし，どの人も1つも言語を使えない場合は，人と人の間に辺を張れないため，答えは人の数と等しくなる．
 *
 * 連結成分は深さ優先探索などで求めることができる．
 */
#include <iostream>
#include <vector>

using namespace std;

void dfs(int pos, const vector<vector<int> > &matrix, vector<int> &visited) {
    if(visited[pos]) return;
    visited[pos] = 1;
    const vector<int> &row = matrix[pos];
    for(size_t i = 0; i < row.size(); ++i) {
        if(row[i]) dfs(i, matrix, visited);
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int N, M;
    while(cin >> N >> M) {
        vector<vector<int> > matrix(N+M, vector<int>(N+M, 0));
        bool all_zero = true;
        for(int i = 0; i < N; ++i) {
            int k;
            cin >> k;
            if(k != 0) all_zero = false;
            while(k--) {
                int a;
                cin >> a;
                --a;
                matrix[i][N+a] = matrix[N+a][i] = 1;
            }
        }

        if(all_zero) {
            cout << N << endl;
        } else {
            int groups = 0;
            vector<int> visited(N+M, 0);
            for(int i = 0; i < N; ++i) {
                if(!visited[i]) {
                    ++groups;
                    dfs(i, matrix, visited);
                }
            }
            cout << groups-1 << endl;
        }
    }
    return 0;
}
