//Name: Colorado Potato Beetle
//Level: 4
//Category: 座標圧縮
//Note: Codeforces #150(Div 1)

/*
 * 典型的な座標圧縮．
 * 何かイベントが起きる点だけが問題となるので，その他の点は幅だけ覚えて1区画にまとめてしまう．
 * 最初の1パスでイベント発生点を列挙し，次のパスで圧縮したグリッドに対して線を描画する．
 * 最後に外側と接しているマスを塗り潰し，無事なマスの個数を数えればよい．
 *
 * イベント発生点そのものは幅1の区画にしないとおかしくなる(or 超面倒になる)ので注意．
 *
 * イベント発生点が全部で N 個なので，オーダーは O(N) のはず．
 */
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Tag {
    int dir;
    int step;
    Tag(int d, int s) : dir(d), step(s) {}
};

const int DR[] = {0, 0, -1, 1};
const int DC[] = {-1, 1, 0, 0};
const int ctod(char c) {
    switch(c) {
        case 'L': return 0;
        case 'R': return 1;
        case 'U': return 2;
        case 'D': return 3;
    }
    return -1;
}

void quantize(vector<int> &v, vector<int> &out) {
    sort(v.begin(), v.end());
    //for(int i = 0; i < v.size(); ++i) cout << v[i] << endl;
    v.erase(unique(v.begin(), v.end()), v.end());
    const int N = v.size();
    for(int i = 0; i < N; ++i) {
        if(i > 0 && v[i]-v[i-1] > 1) out.push_back(v[i]-v[i-1]-1);
        out.push_back(1);
    }
}

void paint(vector<vector<int> > &field, int r_, int c_) {
    const int R = field.size();
    const int C = field[0].size();

    queue<pair<int,int> > q;
    q.push(make_pair(r_, c_));
    field[r_][c_] = 2;
    while(!q.empty()) {
        const int r = q.front().first;
        const int c = q.front().second;
        q.pop();
        for(int i = 0; i < 4; ++i) {
            const int nr = r + DR[i];
            const int nc = c + DC[i];
            if(nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
            if(field[nr][nc] != 0) continue;
            field[nr][nc] = 2;
            q.push(make_pair(nr, nc));
        }
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    int N;
    cin >> N;
    vector<Tag> moves;
    vector<int> event_x, event_y;
    int x = 0, y = 0;
    event_x.push_back(x);
    event_y.push_back(y);
    for(int i = 0; i < N; ++i) {
        char c;
        int step;
        cin >> c >> step;
        const int dir = ctod(c);
        moves.push_back(Tag(dir, step));
        x += DC[dir]*step;
        y += DR[dir]*step;
        if(dir == 0 || dir == 1) event_x.push_back(x);
        else event_y.push_back(y);
    }
    vector<int> cell_width, cell_height;
    quantize(event_x, cell_width);
    quantize(event_y, cell_height);
    const int R = cell_height.size();
    const int C = cell_width.size();
    vector<vector<int> > field(R, vector<int>(C, 0));
    x = event_x[0]; y = event_y[0];
    int r = 0, c = 0;
    while(x != 0) x += cell_width[++c];
    while(y != 0) y += cell_height[++r];
    field[r][c] = 1;
    for(int i = 0; i < N; ++i) {
        int diff = 0;
        const Tag &t = moves[i];
        while(diff < moves[i].step) {
            r += DR[t.dir];
            c += DC[t.dir];
            diff += abs(cell_height[r] * DR[t.dir]);
            diff += abs(cell_width[c] * DC[t.dir]);
            field[r][c] = 1;
        }
    }
    for(int r = 0; r < R; ++r) {
        if(field[r][0] == 0) paint(field, r, 0);
        if(field[r][C-1] == 0) paint(field, r, C-1);
    }
    for(int c = 0; c < C; ++c) {
        if(field[0][c] == 0) paint(field, 0, c);
        if(field[R-1][c] == 0) paint(field, R-1, c);
    }
    long long ans = 0;
    for(int r = 0; r < R; ++r) {
        for(int c = 0; c < C; ++c) {
            if(field[r][c] != 2) {
                ans += static_cast<long long>(cell_height[r]) * static_cast<long long>(cell_width[c]);
            }
        }
    }
    cout << ans << endl;
    return 0;
}
