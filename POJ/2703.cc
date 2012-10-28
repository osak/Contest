//Name: Maximum Area Covered by Rectangles
//Level: 4
//Category: 動的計画法,DP
//Note: 入力が制約を満たしてない？

/*
 * 同じ幅の長方形は，高さが一番高いものと二番目に高いものだけ使って，これらをL字形に組み合わせて置けばよい．
 * 幅が違う長方形は包含関係にないので，最終的には階段状に長方形が配置されることになる．
 * 長方形の置き方は y = x に対して左上側と右下側で分けて考えると，最初に長方形をソートしておけば
 * 左上側の最後に置いた長方形の高さと右下側の最後に置いた長方形の幅だけで状態になることがわかる．
 * 幅が一番大きい長方形の組から順に配置していくものとすると，ある状態(h, w) に
 * 長方形(h1,w1)と(w1,h2) (これは(h2,w1)を90度回転させたもの) を置くときに増える面積は
 *   (h1-h)*w1 + (h2-w)*w1
 * となる．
 *
 * これをDPかメモ化再帰すればよいのだが，座標を量子化して配列でメモしたらREになった．
 * mapでメモしたら通った．
 *
 * オーダーは O(N^2)．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>
#include <map>

using namespace std;

typedef pair<int,int> Rectangle;
typedef pair<Rectangle,Rectangle> RectSet;

//vector<int> quantize_dict(100000, -1);
map<int,int> quantize_dict;
void quantize(const vector<RectSet> &v) {
    //fill_n(quantize_dict, sizeof(quantize_dict)/sizeof(int), -1);
    quantize_dict.clear();
    vector<int> h_set;
    for(vector<RectSet>::const_iterator it = v.begin(); it != v.end(); ++it) {
        h_set.push_back(it->first.second);
        h_set.push_back(it->second.second);
    }
    h_set.push_back(0);
    sort(h_set.begin(), h_set.end());
    h_set.erase(unique(h_set.begin(), h_set.end()), h_set.end());
    for(int i = 0; i < (int)h_set.size(); ++i) {
        quantize_dict[h_set[i]] = i;
    }
}

// dp[pos][last_y][last_x]
map<pair<int,int>, int> memo;
int get(int pos, int y, int x) {
    //const int qy = quantize_dict[y];
    //const int qx = quantize_dict[x];
    //assert(qy != -1 && qx != -1);
    const pair<int,int> key(y, x);
    //return dp[pos][qy][qx];
    return memo[key];
}

bool set(int pos, int y, int x, int val) {
    //const int qy = quantize_dict[y];
    //const int qx = quantize_dict[x];
    //assert(qy != -1 && qx != -1);
    const pair<int,int> key(y, x);
    //if(dp[pos][qy][qx] < val) {
    if(!memo.count(key) || memo[key] < val) {
        //dp[pos][qy][qx] = val;
        memo[key] = val;
        return true;
    }
    return false;
}

void clear() {
    //fill_n((int*)dp, sizeof(dp)/sizeof(int), 0);
    memo.clear();
}

void calc(int pos, int y, int x, const vector<RectSet> &v) {
    if(pos == (int)v.size()) return;
    RectSet rs = v[pos];
    const int width = rs.first.first;
    for(int i = 0; i < 2; ++i) {
        const int ny = rs.first.second;
        const int nx = rs.second.second;
        int delta = width*(ny-y) + (nx-x)*width;
        if(pos == 0) delta -= width*width;
        const int nc = get(pos, y, x) + delta;
        //cout << "nc: " << nc << endl;
        if(set(pos+1, ny, nx, nc)) calc(pos+1, ny, nx, v);
        swap(rs.first, rs.second);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    while(true) {
        int M;
        cin >> M;
        if(M == -1) break;
        vector<Rectangle> all_rect;
        for(int i = 0; i < M; ++i) {
            int w, h;
            cin >> w >> h;
            all_rect.push_back(Rectangle(w, h));
        }
        sort(all_rect.begin(), all_rect.end());
        vector<RectSet> rect_sets;
        for(vector<Rectangle>::reverse_iterator it = all_rect.rbegin(); it != all_rect.rend(); ) {
            rect_sets.push_back(RectSet(*it, *(it+1)));
            const int w = it->first;
            while(it != all_rect.rend() && it->first == w) ++it;
        }
        const int N = rect_sets.size();
        quantize(rect_sets);
        clear();
        calc(0, 0, 0, rect_sets);
        int ans = 0;
        /*
        for(int i = 0; i < 201; ++i) {
            for(int j = 0; j < 201; ++j) {
                ans = max(ans, dp[N][i][j]);
            }
        }
        */
        for(map<pair<int,int>,int>::iterator it = memo.begin(); it != memo.end(); ++it) {
            ans = max(ans, it->second);
        }
        cout << ans << endl;
    }
    return 0;
}
