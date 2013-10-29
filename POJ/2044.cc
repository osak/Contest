//Name: Weather Forecast
//Level: 2
//Category: 探索
//Note:

/**
 * 1日ごとに、条件を満たす状態にのみ遷移するようにして探索。
 * 状態としては、各区画が何日連続で晴れたかと、雲の位置がある。
 * 状態数自体は単純に考えて7^16 × 9, 雲がいる位置は必ず0であり、それ以外は1以上であることを考えると
 * 6^12 × 9 = 約200億通りである。
 * このうち、多くの状態は進入禁止制約と7日以上の晴れ禁止制約によって到達不能であることが推測されるので、
 * 普通に探索を行う。
 */
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

typedef unsigned long long ULL;

const int CLOUD[3][3][4] = {
    {
        {0, 1, 4, 5},
        {4, 5, 8, 9},
        {8, 9, 12, 13}
    },
    {
        {1, 2, 5, 6},
        {5, 6, 9, 10},
        {9, 10, 13, 14}
    },
    {
        {2, 3, 6, 7},
        {6, 7, 10, 11},
        {10, 11, 14, 15}
    }
};
const int DX[9] = {1, 2, 0, 0, -1, -2, 0, 0, 0};
const int DY[9] = {0, 0, 1, 2, 0, 0, -1, -2, 0};

inline bool in_range(int a, int x, int b) {
    return a <= x && x < b;
}

int field[16];
bool data[366][16];

ULL hash_(int cx, int cy) {
    ULL res = 0;
    for(int i = 0; i < 16; ++i) {
        res *= 7;
        res += field[i];
    }
    res *= 3;
    res += cy;
    res *= 3;
    res += cx;
    return res;
}

void unhash(ULL v, int &cx, int &cy) {
    cx = v % 3;
    v /= 3;
    cy = v % 3;
    v /= 3;
    for(int i = 16-1; i >= 0; --i) {
        field[i] = v % 7;
        v /= 7;
    }
}

bool solve() {
    int N;
    scanf("%d", &N);
    if(N == 0) return false;
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < 16; ++j) {
            int k;
            scanf("%d", &k);
            data[i][j] = k;
        }
    }
    
    bool ok = true;
    for(int i = 0; i < 16; ++i) {
        field[i] = 1;
    }
    for(int i = 0; i < 4; ++i) {
        field[CLOUD[1][1][i]] = 0;
        if(data[0][CLOUD[1][1][i]]) {
            ok = false;
            break;
        }
    }
    if(ok) {
        vector<ULL> q[2];
        q[0].push_back(hash_(1, 1));
        for(int day = 1; day < N; ++day) {
            const int M = q[0].size();
            if(M == 0) {
                ok = false;
                break;
            }
            //printf("day %d, M: %d\n", day, M);
            q[1].clear();
            for(int i = 0; i < M; ++i) {
                int cx, cy;
                static int store[4];
                unhash(q[0][i], cx, cy);
                for(int j = 0; j < 16; ++j) {
                    field[j]++;
                }
                for(int dir = 0; dir < 9; ++dir) {
                    const int ncx = cx + DX[dir];
                    const int ncy = cy + DY[dir];
                    if(!in_range(0, ncx, 3) || !in_range(0, ncy, 3)) continue;
                    bool valid = true;
                    for(int j = 0; j < 4; ++j) {
                        store[j] = field[CLOUD[ncx][ncy][j]];
                        field[CLOUD[ncx][ncy][j]] = 0;
                        if(data[day][CLOUD[ncx][ncy][j]]) {
                            valid = false;
                        }
                    }
                    if(valid) {
                        for(int j = 0; j < 16; ++j) {
                            if(field[j] >= 7) {
                                valid = false;
                                break;
                            }
                        }
                        if(valid) {
                            /*
                            for(int i = 0; i < 4; ++i) {
                                for(int j = 0; j < 4; ++j) {
                                    printf("%d ", field[i*4+j]);
                                }
                                puts("");
                            }
                            puts("");
                            */
                            q[1].push_back(hash_(ncx, ncy));
                        }
                    }
                    for(int j = 0; j < 4; ++j) {
                        field[CLOUD[ncx][ncy][j]] = store[j];
                    }
                }
            }
            q[0].swap(q[1]);
            sort(q[0].begin(), q[0].end());
            q[0].erase(unique(q[0].begin(), q[0].end()), q[0].end());
        }
        ok = q[0].size() > 0;
    }
    puts(ok ? "1" : "0");
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
