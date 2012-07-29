#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct Tag {
    int mask;
    int x, y;

    Tag() {}
    Tag(int mask, int x, int y) : mask(mask), x(x), y(y) {}

    bool operator <(const Tag &other) const {
        if(mask != other.mask) return mask < other.mask;
        if(x != other.x) return x < other.x;
        return y < other.y;
    }
};

inline bool is_home(int i) {
    return 1 <= i && i <= 24;
}

const int GOAL = 100;
map<Tag, int> memo;

int dfs(vector<vector<int> > &v, int x, int y, int mask, int rem) {
    //cout << x << ' ' << y << ' ' << rem << endl;
    const Tag tag(mask, x, y);
    if(memo.count(tag)) return memo[tag];
    if(rem == -1) return 1;

    const int H = v.size();
    const int W = v[0].size();

    int sum = 0;
    for(int yy = y-1; yy >= 0; --yy) {
        if(v[yy][x] == -1) break;
        if(is_home(v[yy][x]) || (rem == 0 && v[yy][x] == GOAL)) {
            int org = v[yy][x];
            v[yy][x] = -1;
            sum += dfs(v, x, yy, mask|(1<<org-1), rem-1);
            v[yy][x] = org;
        }
    }
    for(int yy = y+1; yy < H; ++yy) {
        if(v[yy][x] == -1) break;
        if(is_home(v[yy][x]) || (rem == 0 && v[yy][x] == GOAL)) {
            int org = v[yy][x];
            v[yy][x] = -1;
            sum += dfs(v, x, yy, mask|(1<<org-1), rem-1);
            v[yy][x] = org;
        }
    }
    for(int xx = x-1; xx >= 0; --xx) {
        if(v[y][xx] == -1) break;
        if(is_home(v[y][xx]) || (rem == 0 && v[y][xx] == GOAL)) {
            int org = v[y][xx];
            v[y][xx] = -1;
            sum += dfs(v, xx, y, mask|(1<<org-1), rem-1);
            v[y][xx] = org;
        }
    }
    for(int xx = x+1; xx < W; ++xx) {
        if(v[y][xx] == -1) break;
        if(is_home(v[y][xx]) || (rem == 0 && v[y][xx] == GOAL)) {
            int org = v[y][xx];
            v[y][xx] = -1;
            sum += dfs(v, xx, y, mask|(1<<org-1), rem-1);
            v[y][xx] = org;
        }
    }

    return memo[tag] = sum;
}

int main() {
    while(true) {
        int M, N;
        cin >> M >> N;
        if(!M && !N) break;

        vector<vector<int> > v(N, vector<int>(M, 0));

        int sx, sy;
        int home_idx = 1;
        int rem = 0;
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < M; ++j) {
                cin >> v[i][j];
                if(v[i][j] == 1) {
                    v[i][j] = home_idx++;
                    ++rem;
                }
                else if(v[i][j] == 2) {
                    sx = j;
                    sy = i;
                    v[i][j] = GOAL;
                }
            }
        }

        memo.clear();
        cout << dfs(v, sx, sy, 0, rem) << endl;
    }

    return 0;
}
