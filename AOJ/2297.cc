//Name: Rectangular Stamps
//Level: 3
//Category: 幅優先探索,BFS
//Note:

/*
 * 状態は一見4^16に見えるが，各マスが正しい色かどうかだけを覚えていれば十分なので2^16状態まで落とせる．
 * 状態遷移は普通に文字列配列を更新するようにするとTLEする恐れがある
 * (置き方が最大49通り * 大きさ最大16 * スタンプ最大16個 * 2^16状態 = 約8億)
 * ので，全ての置き方に対してビットマスクを作成し，ビット演算のみで状態を更新できるようにするとよい．
 *
 * オーダーは紙のマス数をMとして O(NM*2^M)．ただしM=16．
 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

const int INF = 20;
int memo[1<<16];
int mask[3];

inline int color2idx(char c) {
    if(c == 'R') return 0;
    if(c == 'G') return 1;
    if(c == 'B') return 2;
    return -1;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    int N;
    cin >> N;
    vector<int> stamps;
    for(int i = 0; i < N; ++i) {
        int h, w;
        cin >> h >> w;
        for(int py = -h+1; py < 4; ++py) {
            for(int px = -w+1; px < 4; ++px) {
                int stamp = 0;
                for(int dy = 0; dy < h; ++dy) {
                    for(int dx = 0; dx < w; ++dx) {
                        const int x = px+dx;
                        const int y = py+dy;
                        if(0 <= x && x < 4 && 0 <= y && y < 4) {
                            stamp |= 1<<(y*4+x);
                        }
                    }
                }
                stamps.push_back(stamp);
            }
        }
    }
    for(int y = 0; y < 4; ++y) {
        for(int x = 0; x < 4; ++x) {
            char c;
            cin >> c;
            mask[color2idx(c)] |= 1<<(y*4+x);
        }
    }
    queue<pair<int,int> > q;
    q.push(make_pair(0, 0));
    fill_n(memo, 1<<16, INF);
    int ans = INF;
    while(!q.empty()) {
        const int turn = q.front().first;
        const int state = q.front().second;
        q.pop();

        if(memo[state] < turn) continue;
        memo[state] = turn;
        if(state == (1<<16)-1) {
            ans = turn;
            break;
        }

        for(vector<int>::const_iterator it = stamps.begin(); it != stamps.end(); ++it) {
            for(int color = 0; color < 3; ++color) {
                int next_state = state;
                for(int mc = 0; mc < 3; ++mc) {
                    if(color == mc) {
                        next_state |= *it & mask[mc];
                    } else {
                        next_state &= ~(*it & mask[mc]);
                    }
                }
                if(memo[next_state] > turn+1) {
                    memo[next_state] = turn+1;
                    q.push(make_pair(turn+1, next_state));
                }
            }
        }
    }

    cout << ans << endl;
    return 0;
}
