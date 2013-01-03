#include <iostream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

struct Tag {
    int color;
    int ver_count, hor_count;
    Tag() : color(-1), ver_count(0), hor_count(0) {}
};

void detect(const vector<string> &field, vector<vector<int> > &group) {
    const int H = field.size();
    const int W = field[0].size();
    vector<vector<Tag> > dp(H, vector<Tag>(W));
    for(int y = 0; y < H; ++y) {
        for(int x = 0; x < W; ++x) {
            if(!isdigit(field[y][x])) continue;
            const int color = field[y][x] - '0';
            dp[y][x].color = color;
            if(y > 0) {
                if(dp[y-1][x].color == color) {
                    dp[y][x].ver_count = dp[y-1][x].ver_count;
                }
            }
            if(x > 0) {
                if(dp[y][x-1].color == color) {
                    dp[y][x].hor_count = dp[y][x-1].hor_count;
                }
            }
            dp[y][x].hor_count++;
            dp[y][x].ver_count++;
        }
    }
    vector<vector<unsigned char> > hor_filled(H, vector<unsigned char>(W, 0)); 
    vector<vector<unsigned char> > ver_filled(H, vector<unsigned char>(W, 0)); 
    for(int y = H-1; y >= 0; --y) {
        for(int x = W-1; x >= 0; --x) {
            const int color = dp[y][x].color;
            if(color == -1) continue;
            // Horizontal fill
            if(dp[y][x].hor_count >= 3 && !hor_filled[y][x]) {
                int tmp_x = x;
                while(tmp_x >= 0 && dp[y][tmp_x].color == color) {
                    group[y][tmp_x] = color;
                    hor_filled[y][tmp_x] = 1;
                    --tmp_x;
                }
            }
            // Vertical fill
            if(dp[y][x].ver_count >= 3 && !ver_filled[y][x]) {
                int tmp_y = y;
                while(tmp_y >= 0 && dp[tmp_y][x].color == color) {
                    group[tmp_y][x] = color;
                    ver_filled[tmp_y][x] = 1;
                    --tmp_y;
                }
            }
        }
    }
}

void paint(int y, int x, const vector<vector<int> > &group, vector<vector<unsigned char> > &visited) {
    const int H = group.size();
    const int W = group[0].size();
    const static int dy[] = {0, 1, 0, -1};
    const static int dx[] = {1, 0, -1, 0};
    const int color = group[y][x];
    visited[y][x] = 1;
    for(int i = 0; i < 4; ++i) {
        const int ny = y + dy[i];
        const int nx = x + dx[i];
        if(nx < 0 || nx >= W || ny < 0 || ny >= H) continue;
        if(!visited[ny][nx] && group[ny][nx] == color) paint(ny, nx, group, visited);
    }
}

int count_group(const vector<vector<int> > &group) {
    const int H = group.size();
    const int W = group[0].size();
    vector<vector<unsigned char> > visited(H, vector<unsigned char>(W, 0));
    int res = 0;
    for(int y = 0; y < H; ++y) {
        for(int x = 0; x < W; ++x) {
            if(group[y][x] != -1 && !visited[y][x]) {
                ++res;
                paint(y, x, group, visited);
            }
        }
    }
    return res;
}

void print_group(const vector<vector<int> > &group) {
    const int H = group.size();
    const int W = group[0].size();
    for(int y = 0; y < H; ++y) {
        for(int x = 0; x < W; ++x) {
            cout << group[y][x] << ' ';
        }
        cout << endl;
    }
}

void relax(vector<string> &field, const vector<vector<int> > &group) {
    const int H = group.size();
    const int W = group[0].size();
    for(int y = 0; y < H; ++y) {
        for(int x = 0; x < W; ++x) {
            // Mark for empty
            if(group[y][x] != -1) field[y][x] = '*';
        }
    }
    for(int y = H-1; y >= 0; --y) {
        for(int x = W-1; x >= 0; --x) {
            if(isdigit(field[y][x])) {
                int tmp_y = y;
                while(tmp_y+1 < H && field[tmp_y+1][x] == '*') {
                    field[tmp_y+1][x] = field[tmp_y][x];
                    field[tmp_y][x] = '*';
                }
            }
        }
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    int H, W;
    cin >> H >> W;
    vector<string> field(H);
    for(int i = 0; i < H; ++i) {
        cin >> field[i];
    }
    int ans = 0;
    vector<vector<int> > group(H, vector<int>(W, -1));
    detect(field, group);
    //print_group(group);
    const int cnt = count_group(group);
    ans += cnt;
    //relax(field, group);
    cout << ans << endl;
    return 0;
}
