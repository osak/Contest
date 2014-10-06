//Name: Count the Regions
//Level: 3
//Category: 塗りつぶし,座標圧縮
//Note:

/**
 * x座標をひとつ固定して、縦に連なったピクセルを縦ベクトルとして考えると、y軸に平行な辺が存在しない箇所ではずっと同じベクトルが続く。
 * したがって、この区間は1ピクセルにまとめてしまってよい。
 * y座標に関しても同じことが言える。
 *
 * この前処理を行うと、全体が O(N^2) ピクセルの画像として表されるので、塗りつぶしで領域の個数を求めることができる。
 * 辺は1ピクセルを専有し、かつ偶数座標にしか存在しないものとして扱うと楽に実装できる。
 * （元の状態におけるピクセルと辺を両方ともピクセルとして扱う）
 *
 * オーダーは O(N^2)。
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct Dict {
    vector<int> elem;
    unordered_map<int,int> dict;

    void put(int i) {
        elem.push_back(i);
    }

    void gen() {
        sort(begin(elem), end(elem));
        elem.erase(unique(begin(elem), end(elem)), end(elem));
        for(auto i : elem) {
            const int idx = dict.size();
            dict[i] = idx;
        }
    }

    int get(int i) {
        return dict[i];
    }

    int rev(int i) {
        return elem[i];
    }

    int size() const {
        return elem.size();
    }
};

struct Rect {
    int l, t, r, b;
};

void put(Dict &d, int v) {
    d.put(v-1);
    d.put(v);
    d.put(v+1);
}

const int DR[] = {0, -1, 0, 1};
const int DC[] = {1, 0, -1, 0};
void paint(vector<vector<int>> &field, int r, int c) {
    static vector<pair<int,int>> q;
    q.clear();
    q.emplace_back(r, c);
    field[r][c] = 1;
    while(!q.empty()) {
        const auto cur = q.back();
        q.pop_back();
        for(int d = 0; d < 4; ++d) {
            const int nr = cur.first + DR[d];
            const int nc = cur.second + DC[d];
            if(nr < 0 || field.size() <= nr || nc < 0 || field[0].size() <= nc) continue;
            if(field[nr][nc]) continue;
            field[nr][nc] = 1;
            q.emplace_back(nr, nc);
        }
    }
}

bool solve() {
    int N;
    if(!(cin >> N)) return false;
    if(!N) return false;

    Dict xdict, ydict;
    vector<Rect> rects(N);
    for(int i = 0; i < N; ++i) {
        Rect &r = rects[i];
        cin >> r.l >> r.t >> r.r >> r.b;
        r.l *= 2;
        r.t *= 2;
        r.r *= 2;
        r.b *= 2;
        put(xdict, r.l);
        put(xdict, r.r);
        put(ydict, r.t);
        put(ydict, r.b);
    }
    xdict.gen();
    ydict.gen();

    vector<vector<int>> field(ydict.size(), vector<int>(xdict.size(), 0));
    for(const auto &re : rects) {
        const int l = xdict.get(re.l);
        const int r = xdict.get(re.r);
        const int t = ydict.get(re.t);
        const int b = ydict.get(re.b);
        for(int i = l; i <= r; ++i) {
            field[t][i] = field[b][i] = 1;
        }
        for(int i = b; i <= t; ++i) {
            field[i][l] = field[i][r] = 1;
        }
    }

    int ans = 0;
    for(int r = 0; r < field.size(); ++r) {
        for(int c = 0; c < field[0].size(); ++c) {
            if(field[r][c] == 0) {
                paint(field, r, c);
                ++ans;
            }
        }
    }
    cout << ans << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
