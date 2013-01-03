#include <iostream>
#include <vector>
#include <string>
#include <tr1/unordered_map>

using namespace std;

vector<string> field;
int W, H;
struct Tag {
    vector<int> row_cnt;
    vector<int> col_cnt;
    unsigned row_cleared, col_cleared;
    int total;

    Tag(int width, int height) : 
        row_cnt(vector<int>(width, 0)), col_cnt(vector<int>(height, 0)),
        row_cleared(0), col_cleared(0), total(0){}
    Tag(const Tag &other) {
        row_cnt = other.row_cnt;
        col_cnt = other.col_cnt;
        total = other.total;
        row_cleared = other.row_cleared;
        col_cleared = other.col_cleared;
    }

    void clear_row(int r) {
        if(row_cleared & (1<<r)) return;
        row_cleared |= (1<<r);
        for(int c = 0; c < W; ++c) {
            if(!(col_cleared & (1<<c))) {
                if(field[r][c] == '#') {
                    --row_cnt[c];
                    --col_cnt[r];
                    --total;
                }
            }
        }
    }

    void clear_col(int c) {
        if(col_cleared & (1<<c)) return;
        col_cleared |= (1<<c);
        for(int r = 0; r < H; ++r) {
            if(!(row_cleared & (1<<r))) {
                if(field[r][c] == '#') {
                    --row_cnt[c];
                    --col_cnt[r];
                    --total;
                }
            }
        }
    }

    bool putable(int r, int c) const {
        return (row_cleared & (1<<r)) || (col_cleared & (1<<c)) || field[r][c] == '.';
    }

    bool operator ==(const Tag &other) const {
        //return row_cleared == other.row_cleared && col_cleared == other.col_cleared;
        return row_cnt == other.row_cnt && col_cnt == other.col_cnt && total == other.total;
    }
};

struct Hash {
    size_t operator()(const Tag &tag) const {
        size_t row_hash = 0;
        size_t col_hash = 0;
        for(int c = 0; c < W; ++c) {
            row_hash <<= 2;
            row_hash += tag.row_cnt[c];
        }
        for(int r = 0; r < H; ++r) {
            col_hash <<= 2;
            col_hash += tag.col_cnt[r];
        }
        return row_hash + col_hash;
        //return (tag.row_cleared << 16) + tag.col_cleared;
    }
};

tr1::unordered_map<Tag, int, Hash> memo;
int best = 1000;
int dfs(const Tag &tag, int step) {
    if(memo.count(tag) > 0 && memo[tag] <= step) return best;
    memo[tag] = step;
    if(tag.total == 0) {
        best = min(best, step);
        return best;
    }
    for(int r = 0; r < H; ++r) {
        for(int c = 0; c < W; ++c) {
            if(tag.putable(r, c)) {
                Tag new_tag = tag;
                new_tag.clear_row(r);
                new_tag.clear_col(c);
                dfs(new_tag, step+1);
            }
        }
    }
    return best;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> H >> W;
    field.resize(H);
    Tag tag(W, H);
    for(int r = 0; r < H; ++r) {
        cin >> field[r];
        for(int c = 0; c < W; ++c) {
            if(field[r][c] == '#') {
                ++tag.row_cnt[c];
                ++tag.col_cnt[r];
                ++tag.total;
            }
        }
    }
    dfs(tag, 0);
    if(best == 1000) best = -1;
    cout << best << endl;

    return 0;
}
