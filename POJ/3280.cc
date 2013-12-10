//Name: Cheapest Palindrome
//Level: 3
//Category: 動的計画法,DP
//Note:

/**
 * 範囲[left, right)を回文にするコストを考える。
 * このとき、状態遷移は以下の5通りが存在する。
 * ・leftとright-1が同じ文字のとき、[left+1, right-1)を回文にする。
 * ・leftを使い、右端に同じ文字を加えて[left+1, right)を回文にする。
 * ・leftを捨て、[left+1, right)を回文にする。
 * ・right-1を使い、左端に同じ文字を加えて[left, right-1)を回文にする。
 * ・right-1を捨て、[left, right-1)を回文にする。
 * これをメモ化再帰によって求める。
 *
 * オーダーはO(M^2)。
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

const int MAX = 10000*2000;
struct Tag {
    int ins, del;
};

char str[2000];
Tag cost[256];

int memo[2001][2001];
bool visited[2001][2001];
int calc(int left, int right) {
    if(visited[left][right]) return memo[left][right];
    visited[left][right] = true;
    int &res = memo[left][right];
    res = MAX;
    if(left >= right) return res = 0;

    // Use left
    if(str[left] == str[right-1]) {
        res = min(res, calc(left+1, right-1));
    } else {
        res = min(res, calc(left+1, right) + cost[str[left]].ins);
    }
    // Ignore left
    res = min(res, calc(left+1, right) + cost[str[left]].del);
    // Use right
    res = min(res, calc(left, right-1) + cost[str[right-1]].ins);
    // Ignore right
    res = min(res, calc(left, right-1) + cost[str[right-1]].del);
    return res;
}

bool solve() {
    int N, M;
    scanf("%d %d", &N, &M);
    scanf(" %s", str);
    TIMES(_, N) {
        char c;
        int ins, del;
        scanf(" %c %d %d", &c, &ins, &del);
        cost[c].ins = ins;
        cost[c].del = del;
    }
    printf("%d\n", calc(0, M));
    return false;
}

int main() {
    while(solve()) ;
    return 0;
}
