//Name: Dowsing Machine
//Level: 2
//Category: シミュレーション,塗りつぶし,BFS
//Note: RUPC 2014 Day3

/**
 * 問題は次の2段階に分割できる。
 * ・ダウジングマシンの反応が無矛盾かどうか
 * ・候補地点の全てに到達可能かどうか
 *
 * 1つ目は、各反応について候補となった点を列挙し、すべての反応について積集合を取ったとき、
 * 1つ以上候補が残るかで判定できる。
 * ある点が半径rの正方形内に入っているかは、X軸、Y軸それぞれについて中心との距離を出し、どちらもr以下であるかを見れば判定できる。
 * 2つ目は、Dの位置から到達可能なマスを、幅優先探索などで探せばよい。
 *
 * 出力は、
 * ・候補点が存在しないとき、Broken
 * ・到達可能なマスと到達不可能なマスの両方が候補点に含まれるとき、Unknown
 * ・到達可能なマスのみが候補点のとき、Yes
 * ・到達不可能なマスのみが候補点のとき、No
 *
 * オーダーは O(NS + HW)。
 * ただし、S = max(H, W)。
 */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const int DR[] = {0, -1, 0, 1};
const int DC[] = {1, 0, -1, 0};

int H, W;

void paint(int r, int c, vector<string> &field) {
    for(int d = 0; d < 4; ++d) {
        const int nr = r + DR[d];
        const int nc = c + DC[d];
        if(nr < 0 || nr >= H || nc < 0 || nc >= W) continue;
        if(field[nr][nc] != '.') continue;
        field[nr][nc] = 'D';
        paint(nr, nc, field);
    }
}

bool solve() {
    int D, N;
    if(!(cin >> H >> W >> D >> N)) return false;

    vector<string> field(H);
    for(int i = 0; i < H; ++i) {
        cin >> field[i];
    }
    for(int r = 0; r < H; ++r) {
        for(int c = 0; c < W; ++c) {
            if(field[r][c] == 'D') {
                paint(r, c, field);
                goto next;
            }
        }
    }

next:
    vector<int> rs;
    rs.push_back(-1);
    for(int i = 0; i < D; ++i) {
        int r;
        cin >> r;
        rs.push_back(r);
    }
    rs.push_back(max(H, W));

    vector<vector<int>> cnt(H, vector<int>(W, 0));
    for(int i = 0; i < N; ++i) {
        int X, Y, S;
        cin >> X >> Y >> S;
        for(int dy = -rs[S+1]; dy <= rs[S+1]; ++dy) {
            const int y = Y + dy;
            if(y < 0 || y >= H) continue;
            for(int dx = -rs[S+1]; dx <= rs[S+1]; ++dx) {
                const int x = X + dx;
                if(x < 0 || x >= W) continue;
                if(abs(dy) <= rs[S] && abs(dx) <= rs[S]) continue;
                cnt[y][x]++;
            }
        }
    }

    bool broken = true;
    bool can_reach = false;
    bool cant_reach = false;
    for(int r = 0; r < H; ++r) {
        for(int c = 0; c < W; ++c) {
            if(field[r][c] == '#') continue;
            if(cnt[r][c] == N) {
                broken = false;
                if(field[r][c] == 'D') {
                    can_reach = true;
                } else {
                    cant_reach = true;
                }
            }
        }
    }
    if(broken) {
        cout << "Broken" << endl;
    } else if(can_reach && cant_reach) {
        cout << "Unknown" << endl;
    } else {
        cout << (can_reach ? "Yes" : "No") << endl;
    }
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
