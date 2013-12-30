//Name: Corral the Cows
//Level: 4
//Category: 動的計画法,DP,累積和
//Note:

/**
 * 座標圧縮してから累積和を求め、二分探索で幅を決めながら全ての正方形を試す。
 * ただし、試すべき正方形は、ある2つのクローバーが横の辺と縦の辺にくっついているもののみ。
 * （そうでないとき、適当にずらすと内部のクローバー数を変えずにこのような形にできる）
 *
 * オーダーはO(N^2 log N)。
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#define FOREACH(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

struct Point {
    int x, y;

    bool operator < (const Point &other) const {
        return x < other.x;
    }
};

bool bound[20010];
int dict[20010];
Point points[500];
int dp[500*4+10][500*4+10];

int get(int x, int y) {
    if(x < 0 || y < 0) return 0;
    return dp[x][y];
}

int calc(int x, int y, int w) {
    const int xi = x >= 0 ? dict[x] : 0;
    const int yi = y >= 0 ? dict[y] : 0;
    const int rxi = x+w-1 >= 0 ? dict[x+w-1] : 0;
    const int byi = y+w-1 >= 0 ? dict[y+w-1] : 0;
    return get(rxi, byi) - get(xi-1, byi) - get(rxi, yi-1) + get(xi-1, yi-1);
}

bool solve() {
    int C, N;
    if(scanf("%d %d", &C, &N) == EOF) return false;
    if(!C && !N) return false;

    TIMES(i, N) {
        scanf("%d %d", &points[i].x, &points[i].y);
        bound[points[i].x] = true;
        bound[points[i].y] = true;
    }
    if(N == 1) {
        puts("1");
        return true;
    }
    if(C == 1) {
        puts("1");
        return true;
    }
    sort(points, points+N);
    TIMES(i, 20001) {
        if(i == 0) {
            dict[i] = 0;
        } else {
            if(bound[i] || bound[i-1]) {
                dict[i] = dict[i-1]+1;
            } else {
                dict[i] = dict[i-1];
            }
        }
    }
    const int K = dict[20000]+1;
    TIMES(i, N) {
        dp[dict[points[i].x]][dict[points[i].y]]++;
    }
    TIMES(x, K) {
        TIMES(y, K) {
            dp[x][y] += get(x-1, y) + get(x, y-1) - get(x-1, y-1);
        }
    }

    vector<int> width_list;
    width_list.push_back(0);
    width_list.push_back(1);
    TIMES(i, N) {
        TIMES(j, i) {
            width_list.push_back(abs(points[i].x - points[j].x)+1);
            width_list.push_back(abs(points[i].y - points[j].y)+1);
        }
    }
    sort(width_list.begin(), width_list.end());
    width_list.erase(unique(width_list.begin(), width_list.end()), width_list.end());

    int left = 0, right = width_list.size()-1;
    while(left+1 < right) {
        const int center = (left+right) / 2;
        const int w = width_list[center];
        bool ok = false;
        TIMES(j, N) {
            TIMES(i, j) {
                if(abs(points[i].x - points[j].x) > w) continue;
                if(abs(points[i].y - points[j].y) > w) continue;
                //if(points[i].x == points[j].x && points[i].y == points[j].y) continue;

                // points[i] determines x bound
                if(points[j].y >= points[i].y) { // points[j] determines bottom
                    if(calc(points[i].x, points[j].y-w+1, w) >= C) {
                        ok = true;
                        goto next;
                    }
                }
                if(points[j].y <= points[i].y) { // points[j] determines top
                    if(calc(points[i].x, points[j].y, w) >= C) {
                        ok = true;
                        goto next;
                    }
                }
                // points[j] determins x bound
                if(points[i].y >= points[j].y) { // points[i] determines bottom
                    if(calc(points[j].x-w+1, points[i].y-w+1, w) >= C) {
                        ok = true;
                        goto next;
                    }
                }
                if(points[i].y <= points[j].y) { // points[i] determines top
                    if(calc(points[j].x-w+1, points[i].y, w) >= C) {
                        ok = true;
                        goto next;
                    }
                }
            }
        }
next:
        if(ok) {
            right = center;
        } else {
            left = center;
        }
    }
    printf("%d\n", width_list[right]);
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
