#include "training.h"
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

vector<int> stones;
vector<int> invnum; // 区間[0, k]の転倒数
int N;

inline int get_invnum(int n) {
    if(n < 0) return 0;
    return invnum[n];
}

void init(int N_, int A[])
{
    N = N_;
    stones.insert(stones.begin(), A, A+N);
    invnum.resize(N, 0);
    for(int i = 0; i < N; ++i) {
        if(i > 0) invnum[i] = invnum[i-1];
        for(int j = 0; j < i; ++j) {
            if(stones[j] > stones[i]) invnum[i]++;
        }
    }
}

void update(int pos, int x)
{
    int new_inv = get_invnum(pos-1);
    for(int i = 0; i < pos; ++i) {
        if(stones[i] > x) ++new_inv;
    }

    int inv_diff = 0;
    for(int i = pos+1; i < N; ++i) {
        invnum[i] += new_inv - get_invnum(pos-1);
        invnum[i] += inv_diff;
        if(stones[pos] < stones[i] && x > stones[i]) {
            ++invnum[i];
            ++inv_diff;
        }
        else if(stones[pos] > stones[i] && x < stones[i]) {
            --invnum[i];
            --inv_diff;
        }
    }

    stones[pos] = x;
    invnum[pos] = new_inv;
}

int train(int p, int q)
{
    return get_invnum(q) - get_invnum(p-1);
}
