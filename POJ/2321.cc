//Name: GYM
//Level: 1
//Category: シミュレーション,やるだけ
//Note:

/*
 * 式の通りに10回計算するだけ．
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <cstdio>

using namespace std;

#define FOREACH(it,c) for(__typeof(c.begin()) it = c.begin(); it != c.end(); ++it)

int matrix[10][10];
double sum[10];
double prob[2][10];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N;
    for(int row = 0; ; ++row) {
        string str;
        if(!getline(cin, str)) break;
        istringstream is(str);
        int pos = 0;
        while(!is.eof()) {
            int val;
            is >> val;
            matrix[row][pos] = val;
            sum[row] += val;
            ++pos;
        }
        N = pos;
    }
    double *cur = prob[0], *prev = prob[1];
    fill_n(prev, N, 0);
    prev[0] = 1;
    for(int i = 0; i < 10; ++i) {
        for(int j = 0; j < N; ++j) {
            printf("%s%.5f", (j==0?"":" "), prev[j]);
        }
        puts("");
        
        fill_n(cur, N, 0);
        for(int j = 0; j < N; ++j) {
            for(int k = 0; k < N; ++k) {
                cur[j] += prev[k] * matrix[k][j] / sum[k];
            }
        }
        swap(cur, prev);
    }
    return 0;
}
