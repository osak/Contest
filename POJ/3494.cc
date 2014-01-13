//Name: Largest Submatrix of All 1's
//Level: 3
//Category: 動的計画法,DP,最大長方形
//Note:

/**
 * hist[r][c] = [r][c]から右方向に連続する1の数
 * とすると、各列についてヒストグラムの最大長方形問題を解けば良い。
 * この問題はスタックを使って、常に高さが昇順になるように部分的な長方形を管理するようにすると解ける。
 *
 * オーダーはO(N^2)。
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

int R, C;
int hist[2000][2000];
int calc(int col) {
    static vector<pair<int,int> > stk;
    stk.clear();
    stk.push_back(make_pair(0, 0));
    int ans = 0;
    TIMES(r, R) {
        const int h = hist[r][col];
        int acc = 0;
        while(stk.size() > 0 && stk.back().first >= h) {
            acc += stk.back().second;
            ans = max(ans, stk.back().first * acc);
            stk.pop_back();
        }
        stk.push_back(make_pair(h, acc+1));
    }
    {
        int acc = 0;
        while(stk.size() > 0) {
            acc += stk.back().second;
            ans = max(ans, stk.back().first * acc);
            stk.pop_back();
        }
    }
    return ans;
}

bool solve() {
    if(scanf("%d %d", &R, &C) == EOF) return false;
    if(!R && !C) return false;
    
    TIMES(r, R) {
        TIMES(c, C) {
            scanf("%d", &hist[r][c]);
        }
        for(int c = C-2; c >= 0; --c) {
            if(hist[r][c] == 1) hist[r][c] += hist[r][c+1];
        }
    }

    int ans = 0;
    TIMES(c, C) {
        ans = max(ans, calc(c));
    }
    printf("%d\n", ans);
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
