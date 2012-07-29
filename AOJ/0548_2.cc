#include <iostream>
#include <vector>
#include <cstring>
#include <utility>
#include <map>

using namespace std;

enum Direction {
    EAST, WEST, NORTH, SOUTH
};

struct Home {
    int index;
    Home *neighbor[4];
};

const int GOAL = 100;

Home homes[10][10];

int dfs(Home *cur, int mask, int rem) {
    int sum = 0;

    for(int dir = 0; dir < 4; ++dir) {
        Home *next = cur->neighbor[dir];
        while(next) {
            if(rem == 0) {
                if(next->index == GOAL) return 1;
            }
            if(next->index != GOAL && !(mask&(1<<next->index))) {
                sum += dfs(next, mask|(1<<next->index), rem-1);
                break;
            }
            next = next->neighbor[dir];
        }
    }
    return sum;
}

int main() {
    while(true) {
        int N, M;
        cin >> M >> N;
        if(!N && !M) break;

        memset(homes, 0, sizeof(homes));
        for(int i = 0; i < 10; ++i) {
            for(int j = 0; j < 10; ++j) {
                homes[i][j].index = -1;
            }
        }

        int home_idx = 0;
        int rem = 0;
        int sr, sc;
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < M; ++j) {
                int val;
                cin >> val;
                if(val != 0) {
                    if(val == 1) {
                        homes[i][j].index = home_idx++;
                        ++rem;
                    }
                    else {
                        homes[i][j].index = GOAL;
                        sr = i;
                        sc = j;
                    }

                    for(int jj = j-1; jj >= 0; --jj) {
                        if(homes[i][jj].index != -1) {
                            homes[i][jj].neighbor[EAST] = &homes[i][j];
                            homes[i][j].neighbor[WEST] = &homes[i][jj];
                            break;
                        }
                    }
                    for(int ii = i-1; ii >= 0; --ii) {
                        if(homes[ii][j].index != -1) {
                            homes[ii][j].neighbor[SOUTH] = &homes[i][j];
                            homes[i][j].neighbor[NORTH] = &homes[ii][j];
                            break;
                        }
                    }
                }
            }
        }

        cout << dfs(&homes[sr][sc], 0, rem) << endl;
    }
    return 0;
}
