//Name: Overwriting Game
//Level: 5
//Category: 確率,期待値,数学,Math,分割数,ヤング図形,方程式
//Note:

/**
 * セルを選ぶと左上の領域が必ず塗りつぶされてしまうので、状態として意味があるのは
 * ・一番下から右上にかけて、目的の色が階段状に連続しているマスの並び
 * のみである。
 * 各行に着目すると、このようなマスは全て右詰めで配置されており、かつその数は直下の行以下になることがわかる
 * （直下より多くのマスが目的の色になっていても、その下のマスを塗り替えるときに巻き込まれる）。
 *
 * このような形はヤング図形と呼ばれており、この問題の規模であればあまり個数がなく（O(W^H)、実際には200個程度？）、探索で列挙することができる。
 * これを利用して、「ある状態からゴールまで持っていくときのスコアの期待値」が行列形式で書けるので、方程式を解けばよい。
 *
 * 数がかなり大きくなったり小さくなったりするので、ガウスの消去法を使うときは適切にピボットを選ばないとWAになる。
 *
 * オーダーは O((W^H)^3)。
 */

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <array>
#include <cassert>

using namespace std;

const double EPS = 1e-9;

int H, W;
map<vector<int>,int> dict;
map<int,vector<int>> rev_dict;

// ヤング図形の列挙
void dfs(int prev, vector<int> &buf) {
    if(buf.size() == H) {
        const int idx = dict.size();
        dict[buf] = idx;
        rev_dict[idx] = buf;
    } else {
        for(int i = prev; i <= W; ++i) {
            buf.push_back(i);
            dfs(i, buf);
            buf.pop_back();
        }
    }
}

array<array<int,5>,5> field, goal;

int calc_idx() {
    vector<int> buf(H);
    for(int r = H-1; r >= 0; --r) {
        int cnt = 0;
        for(int c = W-1; c >= 0; --c) {
            if(field[r][c] != goal[r][c]) break;
            ++cnt;
        }
        buf[r] = cnt;
        if(r+1 < H) buf[r] = min(buf[r], buf[r+1]);
    }
    assert(dict.count(buf));
    return dict[buf];
}

// 塗りつぶしのシミュレーション
int paint(int from, int pr, int pc, int color) {
    const vector<int> &young = rev_dict[from];
    for(int r = 0; r < H; ++r) {
        for(int c = 0; c < W; ++c) {
            if(c < W-young[r]) field[r][c] = -1;
            else field[r][c] = goal[r][c];
        }
    }

    for(int r = 0; r <= pr; ++r) {
        for(int c = 0; c <= pc; ++c) {
            field[r][c] = color;
        }
    }
    return calc_idx();
}

bool solve() {
    if(!(cin >> H >> W)) return false;
    if(!H && !W) return false;

    {
        dict.clear();
        rev_dict.clear();
        vector<int> buf;
        dfs(0, buf);
    }
    for(int i = 0; i < H; ++i) {
        string s;
        cin >> s;
        for(int j = 0; j < W; ++j) {
            field[i][j] = (s[j] == 'B');
        }
    }

    for(int i = 0; i < H; ++i) {
        string s;
        cin >> s;
        for(int j = 0; j < W; ++j) {
            goal[i][j] = (s[j] == 'B');
        }
    }
    const vector<int> gy(H, W);
    const int init = calc_idx();
    const int target = dict[gy];

    const int N = dict.size();
    // 期待値ベクトルの最後の要素は定数
    vector<vector<double>> mat(N, vector<double>(N+1, 0));
    for(int from = 0; from < N; ++from) {
        for(int r = 0; r < H; ++r) {
            for(int c = 0; c < W; ++c) {
                for(int color = 0; color < 2; ++color) {
                    const int to = paint(from, r, c, color);
                    mat[from][to] += 1.0 / (H*W*2);
                    mat[from][N] -= (r+1)*(c+1) / double(H*W*2);
                }
            }
        }
    }
    for(int r = 0; r < N; ++r) {
        mat[r][r] -= 1.0;
    }
    for(int c = 0; c < N+1; ++c) {
        if(c != target) mat[target][c] = 0;
    }
    /*
    for(int r = 0; r < N; ++r) {
        for(int c = 0; c < N+1; ++c) {
            cout << mat[r][c] << ' ';
        }
        cout << endl;
    }
    */

    // Gaussian elimination
    vector<bool> done(N, false);
    for(int i = 0; i < N; ++i) {
        // ピボットを探す
        int pivr;
        double pivv = 0.0;
        for(int r = 0; r < N; ++r) {
            if(done[r]) continue;
            if(fabs(mat[r][i]) > fabs(pivv)) {
                pivr = r;
                pivv = mat[r][i];
            }
        }
        if(fabs(pivv) < EPS) continue;

        // ピボットのいる列を掃き出す
        for(int r = 0; r < N; ++r) {
            if(r == pivr) continue;
            const double ratio = mat[r][i] / pivv;
            for(int c = 0; c < N+1; ++c) {
                mat[r][c] -= mat[pivr][c] * ratio;
            }
        }
        done[pivr] = true;
    }
    
    double ans = 1.0 / 0.0;
    for(int r = 0; r < N; ++r) {
        if(fabs(mat[r][init]) > EPS) {
            ans = fabs(mat[r][N] / mat[r][init]);
            break;
        }
    }
    cout << ans << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    while(solve()) ;
    return 0;
}
