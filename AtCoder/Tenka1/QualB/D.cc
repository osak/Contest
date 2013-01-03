#include <iostream>
#include <vector>
#include <string>
#include <tr1/unordered_map>

using namespace std;

typedef unsigned char byte;
typedef vector<vector<byte> > Field;
enum FieldObject {EMPTY, WALL};

struct Hash {
    size_t operator()(const Field &field) const {
        size_t sum = 0;
        int pos = 1;
        for(vector<vector<byte> >::const_iterator it = field.begin(); it != field.end(); ++it) {
            for(vector<byte>::const_iterator it2 = it->begin(); it2 != it->end(); ++it2) {
                sum += pos * *it2;
                ++pos;
            }
        }
        return sum;
    }
};

inline int update_cell(byte &cell) {
    bool wall = (cell == WALL);
    cell = EMPTY;
    return wall?1:0;
}

tr1::unordered_map<Field, int, Hash> memo;
int best = 1000;
int dfs(const Field &field, int step, int remain) {
    const int H = field.size();
    const int W = field[0].size();
    if(memo.count(field) > 0 && memo[field] <= step) return best;
    memo[field] = step;
    if(remain == 0) {
        best = min(best, step);
        return best;
    }
    for(int r = 0; r < H; ++r) {
        for(int c = 0; c < W; ++c) {
            if(field[r][c] == WALL) continue;
            // put a bomb
            Field new_field = field;
            int broken = 0;
            for(int rr = 0; rr < H; ++rr) broken += update_cell(new_field[rr][c]);
            for(int cc = 0; cc < W; ++cc) broken += update_cell(new_field[r][cc]);
            if(broken == 0) continue;
            dfs(new_field, step+1, remain-broken);
        }
    }
    return best;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int H, W;
    cin >> H >> W;

    Field field(H);
    int remain = 0;
    for(int r = 0; r < H; ++r) {
        string str;
        cin >> str;
        field[r].resize(W);
        for(int c = 0; c < W; ++c) {
            field[r][c] = (str[c]=='.' ? EMPTY : WALL);
            if(field[r][c] == WALL) ++remain;
        }
    }
    dfs(field, 0, remain);
    if(best == 1000) best = -1;
    cout << best << endl;

    return 0;
}
